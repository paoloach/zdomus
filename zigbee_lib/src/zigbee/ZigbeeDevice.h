/*
 * ZigbeeDevice.h
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZIGBEEDEVICE_H_
#define ZIGBEEDEVICE_H_

#include <functional>
#include <memory>
#include "../zcl/ZCLAttribute.h"
#include "ZigbeeTypes.h"
#include "zigbee/messageStructure/AnnunceMessage.h"
#include "../zigbee/CmdData.h"
#include "messageStructure/SimpleDescMessage.h"
#include "messageStructure/ReadAttributeResponseMessage.h"
#include "messageStructure/ReqActiveEndpointsMessage.h"
#include "messageStructure/BindTableResponseMessage.h"
#include "AttributeStatusRecord.h"
#include "PowerNodeData.h"
#include "EndpointID.h"
#include "ClusterID.h"
#include "NwkAddr.h"
#include "../zcl/ZCLDataType.h"
#include "ResponseQueue.h"
#include "ResponseCallback.h"
#include "AttributeKey.h"
#include "AttributesKey.h"
#include "AttributesResponseCallback.h"
#include "AttributesResponseQueue.h"

namespace zigbee {

    enum ZDPRequestType {
        SingleRequest = 0,
        Extended = 1
    };

    class ZigbeeDevice {
    public:
        ZigbeeDevice(std::chrono::seconds timeout) : timeout(timeout), powerNodeQueue(timeout), attributeQueue{timeout},
                                                     attributesResponseQueue{this} {};

        virtual ~ZigbeeDevice() = default;

    public:
        using NewAttributeValueCallback = std::function<void(std::shared_ptr<AttributeStatusRecord> &)>;
        using SimpleDescCallback = std::function<void(SimpleDescMessage *)>;
        using AnnunceCallback = std::function<void(AnnunceMessage *)>;
        using BindTableResponseCallback = std::function<void(std::shared_ptr<BindTableResponseMessage>)>;

        virtual bool isPresent() = 0;

        virtual bool enableLog()=0;


        virtual void requestActiveEndpoints(NwkAddr nwkAddr)=0;

        virtual void getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex)=0;


        virtual void requestReset() = 0;

        virtual void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                    ZigbeeAttributeId commandId, ZCLTypeDataType dataType,
                                    uint8_t dataValueLen, uint8_t *dataValue) = 0;

        virtual void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP,
                                 ClusterID clusterID,
                                 const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) = 0;

        virtual void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN],
                                   EndpointID outClusterEP, ClusterID clusterID,
                                   const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) = 0;

        virtual void sendReqDeviceInfo(NwkAddr networkId) =0;


        virtual void requestBindTable(NwkAddr nwkAddrs) = 0;

        virtual void registerForAnnunceMessage(AnnunceCallback) = 0;

        virtual void registerForSimpleDescMessage(SimpleDescCallback) = 0;

        virtual void registerForBindTableMessage(BindTableResponseCallback) = 0;


        virtual void registerForAttributeCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                             ZigbeeAttributeCmdId cmdId, const std::function<void()>) = 0;

        virtual void sendCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                             ZigbeeClusterCmdId commandId,
                             std::vector<uint8_t> data = std::vector<uint8_t>()) = 0;

// --- Attribute value ----
        virtual void requestAttribute(const AttributeKey &key) = 0;

        void registerForAttributeValue(const AttributeKey &key,
                                       std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&callback) {
            attributeQueue.add(key, std::move(callback));
        };

        virtual void requestAttributes(AttributesKey &attributes) = 0;

        void registerForAttributesValue(const AttributesKey &key,
                                        std::unique_ptr<AttributesResponseCallback> &&callback) {
            attributesResponseQueue.add(key, std::move(callback));
        };


        void setAttribute(AttributeKey key, ZCLAttribute *attribute) {
            attributeQueue.setData(key, attribute);
        }

// ---- Power Node ----
        virtual void requestNodePower(NwkAddr nwkAddr) = 0;

        void registerForPowerNode(NwkAddr nwkAddr,
                                  std::unique_ptr<ResponseCallback<std::shared_ptr<PowerNodeData>>> &&callback) {
            powerNodeQueue.add(nwkAddr, std::move(callback));
        }

        void setPowerNode(std::shared_ptr<PowerNodeData> powerNodeData) {
            powerNodeQueue.setData(powerNodeData->nwkAddr, powerNodeData);
        }


    protected:
        std::chrono::seconds timeout;
        ResponseQueue<NwkAddr, std::shared_ptr<PowerNodeData> > powerNodeQueue;
        ResponseQueue<AttributeKey, ZCLAttribute *> attributeQueue;
        AttributesResponseQueue attributesResponseQueue;
    };

} /* namespace zigbee */

#endif /* ZIGBEEDEVICE_H_ */
