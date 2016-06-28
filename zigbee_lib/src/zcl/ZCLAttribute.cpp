/*
 * ZCLAttribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <boost/bind.hpp>
#include <iostream>

#include "Cluster.h"
#include "StatusEnum.h"

namespace zigbee {

    ZCLAttributeNotAvailableException::ZCLAttributeNotAvailableException(Cluster *parent, int attributeId) {
        std::stringstream stream;
        stream << "try to access to not yet available attribute of cluster " << parent->getClusterName() << ", endpoint " << parent->getEndpoint() <<
        ", node "
        << parent->getNetworkAddress();
        message = stream.str();
    }

    const char *ZCLAttributeNotAvailableException::what() const _GLIBCXX_USE_NOEXCEPT {
        return message.c_str();
    }

    std::string ZCLAttributeNotAvailableException::getMessage() const _GLIBCXX_USE_NOEXCEPT {
        return message;
    }


    ZCLAttribute::ZCLAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, int attributeId, ZCLTypeDataType zclType,
                               std::experimental::string_view name, bool readOnly) :
            zigbeeDevice(zigbeeDevice), parent(parent), identifier(attributeId), zclType(zclType), name(name), readOnly(readOnly) {
        status = NotAvailable;
    }


    void ZCLAttribute::requestValue() {
        if (zigbeeDevice != nullptr) {
            zigbeeDevice->requestAttribute(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier);
        }
    }

    void ZCLAttribute::setValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        if (rawData->attributeId == identifier) {
            if (rawData->status == StatusEnum::SUCCESS) {
                if (rawData->attributeDataType == static_cast<ZigbeeAttributeDataType>(getZCLType())) {
                    internalSetValue(rawData);
                    status = Available;
                } else {
                    std::cout << "rawData->attributeDataType: " << (int) (rawData->attributeDataType) << ", expected " << getZCLType() << std::endl;
                }
            } else if (rawData->status == StatusEnum::UNSUPPORTED_ATTRIBUTE) {
                status = NotSupported;
            } else {
                status = Undefined;
            }

            callbacks();
        }
    }

    void ZCLAttribute::setValue(AttributeResponse & attributeResponse) {
        if (attributeResponse.attrID == identifier) {
            if (attributeResponse.status == StatusEnum::SUCCESS) {
                if (attributeResponse.dataType == static_cast<uint8_t >(getZCLType())) {
                    uint8_t * rawData = (uint8_t *)(&attributeResponse) + sizeof(AttributeResponse);
                    internalSetValue(rawData);
                    status = Available;
                } else {
                    std::cout << "rawData->attributeDataType: " << (int) (attributeResponse.dataType) << ", expected " << getZCLType() << std::endl;
                }
            } else if (attributeResponse.status == StatusEnum::UNSUPPORTED_ATTRIBUTE) {
                status = NotSupported;
            } else {
                status = Undefined;
            }

            callbacks();
        }
    }

    void ZCLAttribute::sendValueToDevice(uint8_t dataLen, uint8_t *data) {
        zigbeeDevice->writeAttribute(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier, zclType, dataLen, data);
    }



} /* namespace zigbee */
