//
// Created by paolo on 31/12/16.
//
#include <boost/log/trivial.hpp>
#include <sstream>
#include <iomanip>

#include "SerialDriver.h"

namespace zigbee {
    using boost::asio::serial_port_base;
    using namespace boost::asio;
    using namespace boost::system;
    using std::stringstream;
    using std::hex;
    using std::setw;
    using std::setfill;
    using std::uppercase;
    const int SerialDriver::BAUD_RATE = 115200;
    //const int SerialDriver::BAUD_RATE = 57600;
    static const boost::posix_time::time_duration WEAKUP_TIMER = boost::posix_time::seconds(1);

    SerialDriver::SerialDriver(const std::string &port, boost::asio::io_service &io, SingletonObjects &singletonObjects) : singletonObjects(singletonObjects), port(port),
                                                                                                                           serialPort(io),
                                                                                                                           serialResponseExecutor(singletonObjects) {
        try {
            serialPort.open(port);

            serialPort.set_option(serial_port_base::baud_rate(BAUD_RATE));

            serialPort.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

            serialPort.set_option(serial_port_base::parity(serial_port_base::parity::none));

            serialPort.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

            serialPort.set_option(serial_port_base::character_size(8));

        } catch (system_error &e) {
            BOOST_LOG_TRIVIAL(error) << "Unable to open serial port " << port << " : " << e.what();
            return;
        }

        stop = false;
        readThread = std::thread([this] { run(); });

    }

    SerialDriver::~SerialDriver() {
        serialPort.close();
        stop = true;
        readThread.join();
    }

    void SerialDriver::run() {

        char c;

        while (!stop) {
            try {
                serialPort.read_some(buffer(&c, 1));
                if (c != '\n') {
                    message += c;
                } else {
                    BOOST_LOG_TRIVIAL(info) << message;
                    serialResponseExecutor.execute(message);
                    message = "";
                }
            } catch (system_error &e) {
                BOOST_LOG_TRIVIAL(error) << "Error reading from serial port " << port << " : " << e.what();
            }
        }

    }

    bool SerialDriver::isPresent() {
        return serialPort.is_open();
    }

    bool SerialDriver::enableLog() {
        return false;
    }

    void SerialDriver::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "IEEE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << ", " << (requestType == SingleRequest ? '0' : '1') << ", " << setw(2)
                   << (int) startIndex << "\n";
            std::string data = stream.str();
            serialPort.write_some(buffer(data));
            BOOST_LOG_TRIVIAL(info) << "Send requesT: " << data;
        }
    }

    void SerialDriver::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "RA: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(4) << attributeId << "\n";
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // RAS: networkid, endpointId, clusterId, attributesNum, first attributed id, ..., last attribute id
    //       4 digits, 2 digits  ,  4 digits, 2 digits     ,  4 digits          , ...,    4  digits
    void SerialDriver::requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeIds &attributeIds) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "RAS: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(2) << attributeIds.size();
            for (auto &attributeId: attributeIds) {
                stream  << ", " << hex << setw(4) << attributeId;
                usleep(100000);
            }
            stream << "\n";
            std::string data = stream.str();

            BOOST_LOG_TRIVIAL(info) << "Request: (size:  " << data.size() << ") " << data;
            serialPort.write_some(buffer(data));

        }
    }

    void SerialDriver::requestReset() {
        if (serialPort.is_open()) {
            serialPort.write_some(buffer("RESET:\n"));
        }
    }

    // Send message: WA: networkid, endpointId, clusterId, attributeId, dataType, , dataLen  ,         data
    //                   4 digits ,  2 digits ,  4 digits,  4 digits  ,  2 digits ,  2 digits,  n*2 digits, where n=dataLen
    void SerialDriver::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                      uint8_t *dataValue) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "WA: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(4) << attributeId << ", "  << setw(2) << (int)dataType <<", " << setw(2) << (int)dataValueLen;
            if (dataValueLen > 0) {
                stream << ", ";

                for (int i=0; i < dataValueLen; i++) {
                    stream << hex << uppercase << setfill('0') << setw(2) << (uint32_t) dataValue[i];
                }
            }
            stream << '\n';
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // Send message: SC: networkid, endpointId, clusterId, commandId, dataLen  , data
    //                   4 digits ,  2 digits ,  4 digits,  4 digits,  2 digits,  n*2 digits, where n=dataLen
    void SerialDriver::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "SC: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2) << (int) endpoint.getId() << ", " << setw(4) << cluster.getId()
                   << ", " << setw(4) << commandId  <<", " << setw(2) << data.size();
            if (data.size() > 0) {
                stream << ", ";

                for (uint8_t value: data) {
                    stream << hex << uppercase << setfill('0') << setw(2) << (uint32_t) value;
                }
            }
            stream << '\n';
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // Send message: AE: networkid
    //                    4digit
    void SerialDriver::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "AE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }
    }


    // Send message: NP: networkid
    //                    4digit
    void SerialDriver::requestNodePower(NwkAddr nwkAddr) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "NP: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // Send message: BI: network id, extend address,  endpointId, clusterId, extend address, endpoint Id
    //                    4 digits ,  16 digits    ,    2 digits,  4 digits,  16 digits    ,   2 digits
    void SerialDriver::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                     EndpointID inClusterEp) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "BI: " << hex << uppercase << setfill('0') << setw(4) << destAddr.getId() << ", ";
            for (int i=0; i < Z_EXTADDR_LEN; i++){
                stream << hex << uppercase << setfill('0') << setw(2) << outClusterAddr[i];
            }
            stream << ", " << (int)outClusterEP.getId() << ", " << setw(4) << clusterID.getId() <<", ";
            for (int i=0; i < Z_EXTADDR_LEN; i++){
                stream << hex << uppercase << setfill('0') << setw(2) << inClusterAddr[i];
            }
            stream << ", " << (int)inClusterEp.getId();

            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }

    }

    // Send message: UBI: network id, extend address,  endpointId, clusterId, extend address, endpoint Id
    //                    4 digits ,  16 digits    ,    2 digits,  4 digits,  16 digits    ,   2 digits
    void SerialDriver::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                       EndpointID inClusterEp) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "UBI: " << hex << uppercase << setfill('0') << setw(4) << destAddr.getId() << ", ";
            for (int i=0; i < Z_EXTADDR_LEN; i++){
                stream << hex << uppercase << setfill('0') << setw(2) << outClusterAddr[i];
            }
            stream << ", " << (int)outClusterEP.getId() << ", " << setw(4) << clusterID.getId() <<", ";
            for (int i=0; i < Z_EXTADDR_LEN; i++){
                stream << hex << uppercase << setfill('0') << setw(2) << inClusterAddr[i];
            }
            stream << ", " << (int)inClusterEp.getId();

            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Request: (" << data.size() << "): " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // Send message: DI: networkId
    //                    4 digits
    void SerialDriver::sendReqDeviceInfo(NwkAddr networkId) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "DI: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Send request: " << data;
            serialPort.write_some(buffer(data));
        }
    }

    // Send message: BT network ID
    //                   4 digits
    void SerialDriver::requestBindTable(NwkAddr networkId) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "BI: " << hex << uppercase << setfill('0') << setw(4) << networkId.getId() << "\n";
            std::string data = stream.str();
            BOOST_LOG_TRIVIAL(info) << "Send request: " << data;
            serialPort.write_some(buffer(data));
        }
    }


}
