//
// Created by paolo on 31/12/16.
//
#include <boost/log/trivial.hpp>
#include <boost/date_time.hpp>
#include <boost/fiber/algo/round_robin.hpp>
#include <termios.h>

#include "SerialDriver.h"

namespace zigbee {
    using namespace boost::asio;
    using namespace boost::system;
    using std::stringstream;
    using std::hex;
    using std::setw;
    using std::setfill;
    using std::uppercase;
    const int SerialDriver::BAUD_RATE = B115200;

    SerialDriver::SerialDriver(const std::string &port, boost::asio::io_service &io, SingletonObjects &singletonObjects, std::chrono::seconds timeout) : ZigbeeDevice(timeout),
                                                                                                                                                         singletonObjects(
                                                                                                                                                                 singletonObjects),
                                                                                                                                                         port(port),
                                                                                                                                                         serialResponseExecutor(
                                                                                                                                                                 singletonObjects) {
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
        readThread = std::thread([this] { run(); });

    }

    SerialDriver::~SerialDriver() {
        close(serialFd);
        stop = true;
        readThread.join();
    }


    void SerialDriver::run() {
        boost::fibers::use_scheduling_algorithm<boost::fibers::algo::round_robin>();
        powerNodeQueue.startDequeFiber();
        attributeQueue.startDequeFiber();
        int n;
        fd_set readFd;
        struct timeval timeout;

        while (!stop) {
            std::this_thread::__sleep_for(0s,10us);
            boost::this_fiber::yield();
            FD_ZERO(&readFd);
            FD_SET(serialFd, &readFd);
            timeout.tv_sec = 0;
            timeout.tv_usec = 1;

            while (select(serialFd + 1, &readFd, NULL, NULL, &timeout) > 0) {
                n = read(serialFd, &c, 1);
                if (n > 0) {
                    if (c != '\n') {
                        message += c;
                    } else {
                        BOOST_LOG_TRIVIAL(info) << message;
                        try {
                            serialResponseExecutor.execute(message);
                        } catch (system_error &e) {
                            BOOST_LOG_TRIVIAL(error) << "Error reading from serial port " << port << " : " << e.what();
                        }
                        message = "";
                    }
                }
            }

        }

    }

    bool SerialDriver::isPresent() {
        return serialFd >= 0;
    }

    bool SerialDriver::enableLog() {
        return false;
    }

    void SerialDriver::write(std::string &&data) {
        auto remain = data.length();
        auto start = 0;
        while (remain > 0) {
            auto written = ::write(serialFd, data.c_str() + start, remain);
            start += written;
            remain -= written;
        }
        BOOST_LOG_TRIVIAL(info) << "Send request: " << data;
    }

    void SerialDriver::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "IEEE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << ", " << (requestType == SingleRequest ? '0' : '1') << ", " << setw(2)
                   << (int) startIndex << "\n";
            write(stream.str());
        }
    }

    void SerialDriver::requestAttribute(const AttributeKey &key) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "RA: " << hex << uppercase << setfill('0') << setw(4) << key.networkAddress.getId() << ", " << setw(2) << (int) key.endpoint.getId() << ", " << setw(4)
                   << key.clusterId.getId() << ", " << setw(4) << key.attributeId << "\n";
            write(stream.str());
        }
    }

    // RAS: networkid, endpointId, clusterId, attributesNum, first attributed id, ..., last attribute id
    //       4 digits, 2 digits  ,  4 digits, 2 digits     ,  4 digits          , ...,    4  digits
    void SerialDriver::requestAttributes(AttributesKey &key) {
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

    void SerialDriver::requestReset() {
        if (serialFd >= 0) {
            write(std::string("RESET:\n"));
        }
    }

    // Send message: WA: networkid, endpointId, clusterId, attributeId, dataType, , dataLen  ,         data
    //                   4 digits ,  2 digits ,  4 digits,  4 digits  ,  2 digits ,  2 digits,  n*2 digits, where n=dataLen
    void SerialDriver::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId, ZCLTypeDataType dataType, uint8_t dataValueLen,
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
    void SerialDriver::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data) {
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
    void SerialDriver::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "AE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            write(stream.str());
        }
    }


    // Send message: NP: networkid
    //                    4digit
    void SerialDriver::requestNodePower(NwkAddr nwkAddr) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "NP: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            write(stream.str());
        }
    }

    // Send message: BI: network id, extend address,  endpointId, clusterId, extend address, endpoint Id
    //                    4 digits ,  16 digits    ,    2 digits,  4 digits,  16 digits    ,   2 digits
    void SerialDriver::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
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
    void SerialDriver::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
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
    void SerialDriver::sendReqDeviceInfo(NwkAddr networkId) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "DI: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            write(stream.str());
        }
    }

    // Send message: BT network ID
    //                   4 digits
    void SerialDriver::requestBindTable(NwkAddr networkId) {
        if (serialFd >= 0) {
            stringstream stream;
            stream << "BI: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            write(stream.str());
        }
    }


}
