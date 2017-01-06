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
                                                                                                                           serialPort(io),serialResponseExecutor(singletonObjects) {
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
        stop=true;
        readThread.join();
    }

    void SerialDriver::run() {

        char c;

        while(!stop) {
            try {
                serialPort.read_some(buffer(&c, 1));
                if (c != '\n'){
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

    void SerialDriver::getUsbMessage() {

    }

    void SerialDriver::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "IEEE: " << hex << uppercase << setfill('0') << setw(4) << nwkAddr.getId() << ", " << (requestType == SingleRequest ? '0' : '1') << ", " << setw(2) << (int)startIndex << "\n";
            std::string data = stream.str();
            serialPort.write_some(buffer(data));
            BOOST_LOG_TRIVIAL(info) << "Send requesT: " << data;
        }
     }

    void SerialDriver::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) {
        if (serialPort.is_open()) {
            stringstream stream;
            stream << "RA: " << hex << uppercase << setfill('0') << setw(4) << nwkAddrs.getId() << ", " << setw(2)<< (int)endpoint.getId() << ", " << setw(4) << cluster.getId() << ", "  << setw(4) << attributeId << "\n";
            std::string data = stream.str();
            serialPort.write_some(buffer(data));
        }
    }

    void SerialDriver::requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeIds &attributeIds) {

    }

    void SerialDriver::requestReset() {

    }

    void SerialDriver::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                      uint8_t *dataValue) {

    }

    void SerialDriver::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data) {

    }

    void SerialDriver::registerForAttributeCmd(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeCmdId, const std::function<void()>) {
    }

    void SerialDriver::registerForAttributeValue(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeId, const ZigbeeDevice::NewAttributeValueCallback) {
    }

    // Send message: AE: networkid
    //                    4digit
    void SerialDriver::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (serialPort.is_open()){
            stringstream stream;
            stream << "AE: " << hex <<  uppercase << setfill('0') << setw(4) << nwkAddr.getId() << "\n";
            std::string data = stream.str();
            serialPort.write_some(buffer(data));
        }
    }

    void
    SerialDriver::sendReqBind(NwkAddr destAddr, const uint8_t *outClusterAddr, EndpointID outClusterEP, ClusterID clusterID, const uint8_t *inClusterAddr, EndpointID inClusterEp) {

    }

    void SerialDriver::sendReqUnbind(NwkAddr destAddr, const uint8_t *outClusterAddr, EndpointID outClusterEP, ClusterID clusterID, const uint8_t *inClusterAddr,
                                     EndpointID inClusterEp) {

    }

    void SerialDriver::sendReqDeviceInfo(NwkAddr networkId) {

    }

    void SerialDriver::requestBindTable(NwkAddr nwkAddrs) {

    }


}
