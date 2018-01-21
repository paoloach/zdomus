//
// Created by paolo on 31/12/16.
//

#ifndef DOMUS_ENGINE_SERIALDRIVER2_H
#define DOMUS_ENGINE_SERIALDRIVER2_H

#include <zigbee/ZigbeeDevice.h>
#include <thread>
#include "../Utils/SingletonObjects.h"
#include "Serial2ResponseExecutor.h"
#include "PacketSend.h"

namespace zigbee {
    class SerialDriver2 : public ZigbeeDevice {
    public:
        SerialDriver2(const std::string & port,  SingletonObjects * singletonObjects, std::chrono::seconds timeout);
        virtual ~SerialDriver2();

        bool isPresent() override;

        bool enableLog() override;

        void requestNodePower(NwkAddr nwkAddr) override;

        void getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) override;

        void requestAttribute(const AttributeKey &) override;

        void requestAttributes(AttributesKey & attributesKey) override;

        void requestReset() override;

        void removeDevice(NwkAddr networkId) override;

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

        void registerForAttributeCmd(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeCmdId, const std::function<void()>) override{};

        void requestActiveEndpoints(NwkAddr nwkAddr) override;

        void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                         EndpointID inClusterEp) override;

        void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                           EndpointID inClusterEp) override;

        void sendReqDeviceInfo(NwkAddr networkId) override;

        void requestBindTable(NwkAddr nwkAddrs) override;

    private:
        void run();
        void write(PacketSend && data);
        char c;
        SingletonObjects * singletonObjects;
        std::string port;
        int serialFd;
        std::thread threadRead;
        std::thread threadQueue;
        std::string message;
        bool stop;
        static const int BAUD_RATE;
        std::vector<AnnunceCallback> annunceSignal;
        std::vector<SimpleDescCallback> simpleDescSignal;
        std::vector<BindTableResponseCallback> bindTableResponseSignal;

    };
}

#endif //DOMUS_ENGINE_SERIALDRIVER2_H
