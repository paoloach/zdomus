//
// Created by paolo on 27/01/17.
//

#ifndef DOMUS_ENGINE_DEMODEVICE_H
#define DOMUS_ENGINE_DEMODEVICE_H

#include <zigbee/ZigbeeDevice.h>
#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/unbuffered_channel.hpp>
#include <thread>
#include <random>
#include "../ZigbeeData/ZDevices.h"
#include "../usb/AttributeValuesSignalMap.h"

namespace zigbee {

    class SingletonObjects;

    class DemoDevice : public ZigbeeDevice {
    public:
        explicit DemoDevice(SingletonObjects &singletonObjects);

        virtual ~DemoDevice() = default;
        using PowerNodeSet = boost::fibers::unbuffered_channel<NwkAddr>;
    private:
        bool isPresent() override;

        bool enableLog() override;

        void requestActiveEndpoints(NwkAddr nwkAddr) override;

        void requestNodePower(NwkAddr nwkAddr) override;

        void getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) override;

        void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) override;

        void requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeIds &attributeIds) override;

        void requestReset() override;

        void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                    uint8_t *dataValue) override;

        virtual void
        sendCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data = std::vector<uint8_t>()) override;

        virtual void
        sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                    EndpointID inClusterEp) override;

        virtual void
        sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                      EndpointID inClusterEp) override;

        virtual void sendReqDeviceInfo(NwkAddr networkId) override;


        virtual void requestBindTable(NwkAddr nwkAddrs) override;

        virtual void registerForAnnunceMessage(AnnunceCallback) override;

        virtual void registerForSimpleDescMessage(SimpleDescCallback) override;

        virtual void registerForBindTableMessage(BindTableResponseCallback) override;

        virtual void registerForAttributeCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeCmdId cmdId, const std::function<void()>) override;

        virtual void registerForAttributeValue(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
                                               const NewAttributeValueCallback subscriber) override;

// internal function
        void assignBasicCluster(std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds, std::array<std::vector<uint8_t>, 8> &data);

        void assignTemperatureMeasureCluster(std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds, AttributeValueSignalMap &attributeValueSignalMap, int16_t temp,
                                             int delay);

        void assignOnOffCluster(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds);

        void runDemoThread();

// DATA
        SingletonObjects &singletonObjects;
        PowerNodeSet powerNodeSet;
        bool stop;

        std::thread demoThread;

        std::map<std::tuple<NwkAddr, EndpointID, ClusterID, int>, int> intValuesMap;
        std::vector<std::tuple<int32_t, std::function<void()> > > posponedCallbacks;
        std::vector<boost::fibers::fiber> fibers;

        std::random_device rd;
        std::mt19937 e1;
    };
}


#endif //DOMUS_ENGINE_DEMODEVICE_H
