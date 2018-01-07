//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include "zcl/exceptions/NoUintException.h"
#include "ZCLBitmap16bitAttributeImpl.h"

namespace zigbee {

    std::any ZCLBitmap16bitAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLBitmap16bitAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(std::bitset<16>)) {
            value = std::any_cast<std::bitset<16>>(anyValue);
        } else if (anyValue.type() == typeid(std::uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttributeImpl *attribute) {
        out << attribute->value.to_string();
        return out;
    }

    void ZCLBitmap16bitAttributeImpl::setRawValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        value = converter.value;
    }


}