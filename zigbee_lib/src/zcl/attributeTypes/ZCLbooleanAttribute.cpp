/*
 * ZCLbooleanAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLbooleanAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_boolean_Attribute::ZCL_boolean_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                                 ZigbeeClusterId identifier, std::experimental::string_view name,
                                                 bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeBool>(zigbeeDevice, parent, identifier, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
        }

    }

    ZCL_boolean_Attribute::~ZCL_boolean_Attribute() = default;

    boost::any ZCL_boolean_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_boolean_Attribute::sendValue(bool newValue) {
        sendValueToDevice(1, (uint8_t *) &newValue);
    }

    void ZCL_boolean_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = *rawData->data;
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_boolean_Attribute *attribute) {
        out << (attribute->value ? "true" : "false");
        return out;
    }

    void ZCL_boolean_Attribute::internalSetValue(uint8_t *rawData) {
        value = *rawData;
    }


} /* namespace zigbee */
