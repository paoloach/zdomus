//
// Created by Paolo Achdjian on 11/19/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include <boost/endian/conversion.hpp>
#include "ZCLint32Attribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_int32_Attribute::ZCL_int32_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                             ZigbeeClusterId identifier, std::experimental::string_view name,
                                             bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeSInt32>(zigbeeDevice, parent, identifier, name, readOnly) {
    }

    std::any ZCL_int32_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCL_int32_Attribute::sendValue(int32_t newValue) {
        sendValueToDevice(4, (uint8_t *) &newValue);
    }

    void ZCL_int32_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = boost::endian::little_to_native( *(int32_t *) rawData->data.begin());
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_int32_Attribute *attribute) {
        out << std::hex << attribute->value;
        return out;
    }

    void ZCL_int32_Attribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(int32_t *) rawData);
    }


} /* namespace zigbee */