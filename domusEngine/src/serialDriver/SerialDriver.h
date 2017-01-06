//
// Created by paolo on 31/12/16.
//

#ifndef DOMUS_ENGINE_SERIALDRIVER_H
#define DOMUS_ENGINE_SERIALDRIVER_H

#include <boost/asio.hpp>
#include <zigbee/ZigbeeDevice.h>
#include <thread>
#include "../Utils/SingletonObjects.h"
#include "SerialResponseExecutor.h"

namespace zigbee {
    class SerialDriver : public ZigbeeDevice {
    public:
        SerialDriver(const std::string & port, boost::asio::io_service &serviceIo_, SingletonObjects &singletonObjects);
        virtual ~SerialDriver();

        bool isPresent() override;

        bool enableLog() override;

        void getUsbMessage() override;

        void getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) override;

        void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) override;

        void requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeIds &attributeIds) override;

        void requestReset() override;

        void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                            uint8_t *dataValue) override;

        void sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data = std::vector<uint8_t>()) override;

        void registerForAnnunceMessage(AnnunceCallback subscriber) override {
            annunceSignal.push_back(subscriber);
        }

        void registerForSimpleDescMessage(SimpleDescCallback subscriber) override {
            simpleDescSignal.push_back(subscriber);
        }

        void registerForBindTableMessage(BindTableResponseCallback subscriber) override {
            bindTableResponseSignal.push_back(subscriber);
        }

        void registerForAttributeCmd(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeCmdId, const std::function<void()>) override;

        void registerForAttributeValue(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeId, const NewAttributeValueCallback) override;

        void requestActiveEndpoints(NwkAddr nwkAddr) override;

        void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                         EndpointID inClusterEp) override;

        void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                           EndpointID inClusterEp) override;

        void sendReqDeviceInfo(NwkAddr networkId) override;

        void requestBindTable(NwkAddr nwkAddrs) override;

    private:
        void run();
        SingletonObjects &singletonObjects;
        std::string port;
        boost::asio::serial_port serialPort;
        std::thread readThread;
        std::string message;
        bool stop;
        SerialResponseExecutor serialResponseExecutor;
        static const int BAUD_RATE;
        std::vector<AnnunceCallback> annunceSignal;
        std::vector<SimpleDescCallback> simpleDescSignal;
        std::vector<BindTableResponseCallback> bindTableResponseSignal;
    };
}

#endif //DOMUS_ENGINE_SERIALDRIVER_H
