//
// Created by Paolo Achdjian on 11/19/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//
#include <boost/endian/conversion.hpp>
#include "ZCLuint32Attribute.h"

#include "../Cluster.h"

namespace zigbee {

    ZCL_uint32_Attribute::ZCL_uint32_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                               std::experimental::string_view name, bool readOnly) :
            ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt32, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) { setValue(rawData); });
        }
    }

    boost::any ZCL_uint32_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_uint32_Attribute::sendValue(uint32_t newValue) {
        sendValueToDevice(4, (uint8_t *) &newValue);
    }

    void ZCL_uint32_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = boost::endian::little_to_native( *(uint32_t *) rawData->data);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_uint32_Attribute *attribute) {
        out << std::hex << attribute->value;
        return out;
    }

    void ZCL_uint32_Attribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(uint32_t *) rawData);
    }


} /* namespace zigbee */