/*
 * ZCLAttribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <sstream>
#include <boost/bind.hpp>
#include <iostream>

#include "ZCLAttributeImpl.h"
#include "zcl/Cluster.h"
#include "zcl/StatusEnum.h"
#include "zigbee/ZigbeeDevice.h"

namespace zigbee {
    ZCLAttributeImpl::ZCLAttributeImpl(ZigbeeDevice *  zigbeeDevice, Cluster *parent, int attributeId, ZCLTypeDataType zclType,
                               std::string_view name, bool readOnly) :
            zigbeeDevice(zigbeeDevice), parent(parent), identifier(attributeId), zclType(zclType), name(name), readOnly(readOnly) {
        status = NotAvailable;
    }


    void ZCLAttributeImpl::requestValue(std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&callback) {
        if (zigbeeDevice != nullptr) {
            AttributeKey key{parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier};
            zigbeeDevice->registerForAttributeValue(key, std::move(callback));
            zigbeeDevice->requestAttribute(key);
        }
    }

    void ZCLAttributeImpl::setValue(AttributeResponse & attributeResponse) {
        if (attributeResponse.attrID == identifier) {
            if (attributeResponse.status == StatusEnum::SUCCESS) {
                if (attributeResponse.dataType == static_cast<uint8_t >(getZCLType())) {
                    uint8_t * rawData = (uint8_t *)(&attributeResponse) + sizeof(AttributeResponse);
                    setRawValue(rawData);
                    status = Available;
                } else {
                    BOOST_LOG_TRIVIAL(error)  << "rawData->attributeDataType: " << (int) (attributeResponse.dataType) << ", expected " << getZCLType();
                }
            } else if (attributeResponse.status == StatusEnum::UNSUPPORTED_ATTRIBUTE) {
                status = NotSupported;
            } else {
                status = Undefined;
            }
        }
    }

    void ZCLAttributeImpl::sendValueToDevice(uint8_t dataLen, uint8_t *data) {
        zigbeeDevice->writeAttribute(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier, zclType, dataLen, data);
    }

    void ZCLAttributeImpl::setValue(uint8_t attrStatus, uint8_t dataType, uint8_t *rawData) {
        if (attrStatus == StatusEnum::SUCCESS) {
            if (dataType == static_cast<uint8_t >(getZCLType())) {
                setRawValue(rawData);
                status = Available;
            } else {
                BOOST_LOG_TRIVIAL(error)  << "rawData->attributeDataType: " << (int) (dataType) << ", expected " << getZCLType();
            }
        } else if (attrStatus == StatusEnum::UNSUPPORTED_ATTRIBUTE) {
            status = NotSupported;
        } else {
            status = Undefined;
        }
    }

    void ZCLAttributeImpl::setStatus(uint8_t attrStatus){
        switch (attrStatus){
            case StatusEnum::SUCCESS:
                status = Available;
                break;
            case StatusEnum::UNSUPPORTED_ATTRIBUTE:
                status = NotSupported;
                break;
            default:
                status = Undefined;
        }
    }


} /* namespace zigbee */
