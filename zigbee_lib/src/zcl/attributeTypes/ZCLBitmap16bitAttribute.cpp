//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include "ZCLBitmap16bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCLBitmap16bitAttribute::ZCLBitmap16bitAttribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                                     std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLType16bitBitmap>(zigbeeDevice, parent, identifier, name, readOnly) {
    }

    std::any ZCLBitmap16bitAttribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    bool ZCLBitmap16bitAttribute::getValue(int index) const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return value[index];
    }

    void ZCLBitmap16bitAttribute::sendValue(std::bitset<16> value) {
        auto toSend = value.to_ulong();
        sendValueToDevice(2, (uint8_t *) &toSend);
    }

    void ZCLBitmap16bitAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        Converter converter;
        converter.raw[0] = rawData->data[0];
        converter.raw[1] = rawData->data[1];
        value = converter.value;
    }

    std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttribute *attribute) {
        out << attribute->value.to_string();
        return out;
    }

    void ZCLBitmap16bitAttribute::internalSetValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        value = converter.value;
    }


}