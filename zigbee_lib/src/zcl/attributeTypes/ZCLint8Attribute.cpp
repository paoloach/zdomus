//
// Created by developer on 11/26/15.
//

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "ZCLint8Attribute.h"
#include "../Cluster.h"

namespace zigbee {
    ZCLint8Attribute::ZCLint8Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                       ZigbeeClusterId identifier, std::experimental::string_view name,
                                       bool readOnly) :
            ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeSInt8, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> &attribute) {
                                                        setValue(attribute);
                                                    });
        }
    }


    boost::any ZCLint8Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCLint8Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = *rawData->data;
    }

    void ZCLint8Attribute::sendValue(int8_t newValue) {
        sendValueToDevice(1, (uint8_t *) &newValue);
    }

    std::ostream &operator<<(std::ostream &out, const ZCLint8Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLint8Attribute::internalSetValue(uint8_t *rawData) {
        value = *rawData;
    }


}