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

#include "ZigbeeTypes.h"
#include "zigbee/messageStructure/AnnunceMessage.h"
#include "messageStructure/SimpleDescMessage.h"
#include "messageStructure/ReadAttributeResponseMessage.h"
#include "messageStructure/ReqActiveEndpointsMessage.h"
#include "messageStructure/BindTableResponseMessage.h"
#include "AttributeStatusRecord.h"
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zigbee/NwkAddr.h>
#include "../zcl/ZCLDataType.h"

namespace zigbee {

    class ZigbeeDevice {
    public:
        ZigbeeDevice() = default;

        virtual ~ZigbeeDevice() = default;

    public:
        using NewAttributeValueCallback = std::function<void(std::shared_ptr<AttributeStatusRecord> &)>;
        using SimpleDescCallback = std::function<void(SimpleDescMessage *)>;
        using AnnunceCallback = std::function<void(AnnunceMessage *)>;
        using BindTableResponseCallback = std::function<void(std::shared_ptr<BindTableResponseMessage>)>;

        virtual bool isPresent() = 0;

        virtual bool enableLog()=0;

        virtual bool requestDevices() = 0;

        virtual void getUsbMessage() = 0;

        virtual void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                      ZigbeeAttributeId attributeId) = 0;

        virtual void requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                       ZigbeeAttributeIds &attributeIds) = 0;

        virtual void requestReset() = 0;

        virtual void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                    ZigbeeAttributeId commandId, ZCLTypeDataType dataType,
                                    uint8_t dataValueLen, uint8_t *dataValue) = 0;

        virtual void sendCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                             ZigbeeClusterCmdId commandId,
                             std::vector<uint8_t> data = std::vector<uint8_t>()) = 0;

        virtual void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP,
                                 ClusterID clusterID,
                                 const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) = 0;

        virtual void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN],
                                   EndpointID outClusterEP, ClusterID clusterID,
                                   const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) = 0;


        virtual void requestBindTable(NwkAddr nwkAddrs) = 0;

        virtual void registerForAnnunceMessage(AnnunceCallback) = 0;

        virtual void registerForSimpleDescMessage(SimpleDescCallback) = 0;

        virtual void registerForBindTableMessage(BindTableResponseCallback) = 0;

        virtual void registerForAttributeCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                             ZigbeeAttributeCmdId cmdId, const std::function<void()>) = 0;

        virtual void registerForAttributeValue(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                               ZigbeeAttributeId attributeId,
                                               const NewAttributeValueCallback subscriber) = 0;
    };

} /* namespace zigbee */

#endif /* ZIGBEEDEVICE_H_ */
