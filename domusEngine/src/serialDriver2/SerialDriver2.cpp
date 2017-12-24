//
// Created by paolo on 31/12/16.
//
#include <boost/log/trivial.hpp>
#include <boost/date_time.hpp>
#include <boost/fiber/algo/round_robin.hpp>
#include <termios.h>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>

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

    SerialDriver2::SerialDriver2(const std::string &port, SingletonObjects &singletonObjects, std::chrono::seconds timeout) :
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
        threadRead = std::thread(readThread,std::ref(singletonObjects), serialFd);
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
        if (serialFd >= 0) {
            write("INIT:\n");
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

    void SerialDriver2::write(std::string &&data) {
        auto remain = data.length();
        auto start = 0;
        while (remain > 0) {
            auto written = ::write(serialFd, data.c_str() + start, remain);
            start += written;
            remain -= written;
        }
        BOOST_LOG_TRIVIAL(info) << "Send request: " << data;
    }

    void SerialDriver2::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        if (serialFd >= 0) {
            stringstream stream;
            stream << "IEEE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << ", " << (requestType == SingleRequest ? '0' : '1') << ", " << setw(2)
                   << (int) startIndex << "\n";
            write(stream.str());
        }
    }

    void SerialDriver2::requestAttribute(const AttributeKey &key) {
        std::vector<ZigbeeAttributeId> list;
        list.push_back(key.attributeId);
        AttributesKey keys{key.networkAddress, key.endpoint, key.clusterId,list};
        requestAttributes(keys);
//        if (serialFd >= 0) {
//            stringstream stream;
//            stream << "RA: " << hex << uppercase << setfill('0') << setw(4) << key.networkAddress.getId() << ", " << setw(2) << (int) key.endpoint.getId() << ", " << setw(4)
//                   << key.clusterId.getId() << ", " << setw(4) << key.attributeId << "\n";
//            write(stream.str());
//        }
    }

    // RAS: networkid, endpointId, clusterId, attributesNum, first attributed id, ..., last attribute id
    //       4 digits, 2 digits  ,  4 digits, 2 digits     ,  4 digits          , ...,    4  digits
    void SerialDriver2::requestAttributes(AttributesKey &key) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "RAS: " << hex << uppercase << setfill('0') << setw(4) << key.networkAddress.getId() << ", " << setw(2) << (int) key.endpoint.getId() << ", " << setw(4)
                   << key.clusterId.getId() << ", " << setw(2) << key.attributesId.size();
            for (auto &attributeId: key.attributesId) {
                stream << ", " << hex << setw(4) << attributeId;
                usleep(100000);
            }
            stream << "\n";
            write(stream.str());

        }
    }

    void SerialDriver2::requestReset() {
        if (serialFd >= 0) {
            write(std::string("RESET:\n"));
        }
    }

    // Send message: WA: networkid, endpointId, clusterId, attributeId, dataType, , dataLen  ,         data
    //                   4 digits ,  2 digits ,  4 digits,  4 digits  ,  2 digits ,  2 digits,  n*2 digits, where n=dataLen
    void SerialDriver2::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                      uint8_t *dataValue) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "WA: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(4) << attributeId << ", " << setw(2) << (int) dataType << ", " << setw(2) << (int) dataValueLen;
            if (dataValueLen > 0) {
                stream << ", ";

                for (int i = 0; i < dataValueLen; i++) {
                    stream << hex << uppercase << setfill('0') << setw(2) << (uint32_t) dataValue[i];
                }
            }
            stream << '\n';
            write(stream.str());
        }
    }

    // Send message: SC: networkid, endpointId, clusterId, commandId, dataLen  , data
    //                   4 digits ,  2 digits ,  4 digits,  4 digits,  2 digits,  n*2 digits, where n=dataLen
    void SerialDriver2::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data) {
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        if (serialFd >= 0) {
            stringstream stream;
            stream << "SC: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(4) << commandId << ", " << setw(2) << data.size();
            if (data.size() > 0) {
                stream << ", ";

                for (uint8_t value: data) {
                    stream << hex << uppercase << setfill('0') << setw(2) << (uint32_t) value;
                }
            }
            stream << '\n';
            write(stream.str());
        }
    }

    // Send message: AE: networkid
    //                    4digit
    void SerialDriver2::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "AE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            write(stream.str());
        }
    }


    // Send message: NP: networkid
    //                    4digit
    void SerialDriver2::requestNodePower(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "NP: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            write(stream.str());
        }
    }

    // Send message: BI: network id, extend address,  endpointId, clusterId, extend address, endpoint Id
    //                    4 digits ,  16 digits    ,    2 digits,  4 digits,  16 digits    ,   2 digits
    void SerialDriver2::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                   const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "BI: " << hex << uppercase << setfill('0') << setw(4) << destAddr.getId() << ", ";
            for (int i = 0; i < Z_EXTADDR_LEN; i++) {
                stream << hex << uppercase << setfill('0') << setw(2) << outClusterAddr[i];
            }
            stream << ", " << (int) outClusterEP.getId() << ", " << setw(4) << clusterID.getId() << ", ";
            for (int i = 0; i < Z_EXTADDR_LEN; i++) {
                stream << hex << uppercase << setfill('0') << setw(2) << inClusterAddr[i];
            }
            stream << ", " << (int) inClusterEp.getId();

            write(stream.str());
        }

    }

    // Send message: UBI: network id, extend address,  endpointId, clusterId, extend address, endpoint Id
    //                    4 digits ,  16 digits    ,    2 digits,  4 digits,  16 digits    ,   2 digits
    void SerialDriver2::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                     const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "UBI: " << hex << uppercase << setfill('0') << setw(4) << destAddr.getId() << ", ";
            for (int i = 0; i < Z_EXTADDR_LEN; i++) {
                stream << hex << uppercase << setfill('0') << setw(2) << outClusterAddr[i];
            }
            stream << ", " << (int) outClusterEP.getId() << ", " << setw(4) << clusterID.getId() << ", ";
            for (int i = 0; i < Z_EXTADDR_LEN; i++) {
                stream << hex << uppercase << setfill('0') << setw(2) << inClusterAddr[i];
            }
            stream << ", " << (int) inClusterEp.getId();

            write(stream.str());
        }
    }

    // Send message: DI: networkId
    //                    4 digits
    void SerialDriver2::sendReqDeviceInfo(NwkAddr networkId) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "DI: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            write(stream.str());
        }
    }

    // Send message: BT network ID
    //                   4 digits
    void SerialDriver2::requestBindTable(NwkAddr networkId) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "BT: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            write(stream.str());
        }
    }


}
