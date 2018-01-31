//
// Created by paolo on 31/12/16.
//
#include <boost/log/trivial.hpp>
#include <boost/date_time.hpp>
#include <boost/fiber/algo/round_robin.hpp>
#include <termios.h>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>
#include <boost/asio.hpp>

#include "SerialDriver2.h"
#include "ReadThread.h"

namespace zigbee {
    using namespace boost::asio;
    using namespace boost::system;
    using std::stringstream;
    using std::hex;
    using std::setw;
    using std::setfill;
    using std::uppercase;
    const int SerialDriver2::BAUD_RATE = B115200;
    static const boost::log::string_literal LOG_SCOPE("serial driver");

    static uint8_t SEND_HEADER[3] = {0x45,0x65,0x42};

    SerialDriver2::SerialDriver2(const std::string &port, SingletonObjects * singletonObjects, std::chrono::seconds timeout) :
            ZigbeeDevice(timeout),
            singletonObjects(singletonObjects),
            port(port){
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        serialFd = open(port.c_str(), O_RDWR | O_NOCTTY);
        if (serialFd >= 0) {
            struct termios tty;
            memset(&tty, 0, sizeof tty);

            if (tcgetattr(serialFd, &tty) != 0) {
                BOOST_LOG_TRIVIAL(error) << "Unable to open " << port;
                serialFd = -1;
            } else {
                cfsetospeed(&tty, (speed_t) BAUD_RATE);
                cfsetispeed(&tty, (speed_t) BAUD_RATE);

                tty.c_cflag &= ~PARENB;            // Make 8n1
                tty.c_cflag &= ~CSTOPB;
                tty.c_cflag &= ~CSIZE;
                tty.c_cflag |= CS8;

                tty.c_cflag &= ~CRTSCTS;           // no flow control
                tty.c_cc[VMIN] = 0;                  // read doesn't block
                tty.c_cc[VTIME] = 5;                  // 0.5 seconds read timeout
                tty.c_cflag |= CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

                cfmakeraw(&tty);

                tcflush(serialFd, TCIFLUSH);
                if (tcsetattr(serialFd, TCSANOW, &tty) != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Unable to set port " << port;
                    serialFd = -1;
                }
            }

        } else {
            BOOST_LOG_TRIVIAL(error) << "Unable to open " << port;
        }

        stop = false;
        threadQueue = std::thread([this] { run(); });
        threadRead = std::thread(readThread,singletonObjects, serialFd);
    }

    SerialDriver2::~SerialDriver2() {
        close(serialFd);
        stop = true;
        threadRead.join();
        threadQueue.join();
    }


    void SerialDriver2::run() {
        boost::fibers::use_scheduling_algorithm<boost::fibers::algo::round_robin>();
        powerNodeQueue.startDequeFiber();
        attributeQueue.startDequeFiber();
        ieeeAddressResponseQueue.startDequeFiber();
        nodeDescriptorReponseQueue.startDequeFiber();
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )13);
            write(std::move(data));
        }
        while (!stop) {
            std::this_thread::__sleep_for(0s, 10us);
            boost::this_fiber::yield();
        }
    }

    bool SerialDriver2::isPresent() {
        return serialFd >= 0;
    }

    bool SerialDriver2::enableLog() {
        return false;
    }

    void SerialDriver2::write(PacketSend &&data) {
        ::write(serialFd, &SEND_HEADER, 3 );
        size_t size = data.size();
        ::write(serialFd, &size, 1 );
        ::write(serialFd, data.begin(), size);

        BOOST_LOG_TRIVIAL(info) << "Send request size(" << size << ") : " << data;
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    // 1 byte  -> request type
    // 1 byte  -> start index
    void SerialDriver2::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )1);
            data.push(nwkAddr);
            data.push(static_cast<uint8_t >(requestType));
            data.push(startIndex);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    // 1 byte  -> endpoint
    // 2 bytes -> cluster id
    // 2 bytes -> attribute id
    void SerialDriver2::requestAttribute(const AttributeKey &key) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )2);
            data.push(key.networkAddress);
            data.push(key.endpoint);
            data.push(key.clusterId);
            data.push(key.attributeId);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    // 1 byte  -> endpoint
    // 2 bytes -> cluster id
    // 1 byte  -> number of attributes
    //   2*n bytes -> attributes id
    void SerialDriver2::requestAttributes(AttributesKey &key) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )3);
            data.push(key.networkAddress);
            data.push(key.endpoint);
            data.push(key.clusterId);
            data.push(static_cast<uint8_t>(key.attributesId.size()));
            for(auto & attribute: key.attributesId){
                data.push(attribute);
            }
            write(std::move(data));
        }
    }

    void SerialDriver2::requestReset() {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )4);
            write(std::move(data));
        }
    }


    // 1 byte  -> code
    // 2 bytes -> network id
    // 1 byte  -> endpoint
    // 2 bytes -> cluster id
    // 1 byte  -> data value len
    // 2 bytes -> attributes id
    // 1 byte  -> data type
    // n bytes -> data values
    void SerialDriver2::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                      uint8_t *dataValue) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )5);
            data.push(nwkAddrs);
            data.push(endpoint);
            data.push(cluster);
            data.push(dataValueLen);
            data.push(attributeId);
            data.push(dataType);

            for (int i = 0; i < dataValueLen; i++) {
                data.push(dataValue[i]);
            }
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    // 1 byte  -> endpoint
    // 2 bytes -> cluster id
    // 2 bytes -> commandId id
    // 1 byte  -> data value len
    // n bytes -> data values
    void SerialDriver2::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> values) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )6);
            data.push(nwkAddrs);
            data.push(endpoint);
            data.push(cluster);
            data.push(commandId);
            data.push(static_cast<uint8_t >(values.size()));
            for(uint8_t value: values){
                data.push(value);
            }
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    void SerialDriver2::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )7);
            data.push(nwkAddr);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    void SerialDriver2::requestNodePower(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )8);
            data.push(nwkAddr);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    // 8 bytes -> out cluster addr
    // 1 bytes -> out endpoint id
    // 2 bytes -> cluster id
    // 8 bytes -> in cluster addr
    // 1 byte  -> in endpoint id
    void SerialDriver2::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                   const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )9);
            data.push(destAddr);
            data.push(ExtAddress(outClusterAddr));
            data.push(outClusterEP);
            data.push(clusterID);
            data.push(ExtAddress(inClusterAddr));
            data.push(inClusterEp);
            write(std::move(data));
        }

    }

    void SerialDriver2::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                     const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )10);
            data.push(destAddr);
            data.push(ExtAddress(outClusterAddr));
            data.push(outClusterEP);
            data.push(clusterID);
            data.push(ExtAddress(inClusterAddr));
            data.push(inClusterEp);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    void SerialDriver2::sendReqDeviceInfo(NwkAddr networkId) {
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )11);
            data.push(networkId);
            write(std::move(data));
        }
    }

    // 1 byte  -> code
    // 2 bytes -> network id
    void SerialDriver2::requestBindTable(NwkAddr networkId) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )12);
            data.push(networkId);
            write(std::move(data));
        }
    }

    void SerialDriver2::removeDevice(NwkAddr networkId) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )14);
            data.push(networkId);
            write(std::move(data));
        }
    }


    void SerialDriver2::getNodeDescriptor(NwkAddr networkId) {
        if (serialFd >= 0) {
            PacketSend data;
            data.push((uint8_t )15);
            data.push(networkId);
            write(std::move(data));
        }
    }


}
