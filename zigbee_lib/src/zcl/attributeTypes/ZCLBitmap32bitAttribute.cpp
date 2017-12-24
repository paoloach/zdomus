//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include <boost/endian/conversion.hpp>
#include "ZCLBitmap32bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCLBitmap32bitAttribute::ZCLBitmap32bitAttribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                                     ZigbeeClusterId identifier, std::experimental::string_view name,
                                                     bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLType32bitBitmap>(zigbeeDevice, parent, identifier, name, readOnly){
    }

    std::any ZCLBitmap32bitAttribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    bool ZCLBitmap32bitAttribute::getValue(int index) const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return value[index];
    }

    void ZCLBitmap32bitAttribute::sendValue(std::bitset<32> value) {
        auto toSend = value.to_ulong();
        sendValueToDevice(4, (uint8_t *) &toSend);
    }

    void ZCLBitmap32bitAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = boost::endian::little_to_native( *(uint32_t *) rawData->data.begin());
    }

    std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttribute *attribute) {
        out << attribute->value.to_string();
        return out;
    }

    void ZCLBitmap32bitAttribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(uint32_t *) rawData);
    }


}