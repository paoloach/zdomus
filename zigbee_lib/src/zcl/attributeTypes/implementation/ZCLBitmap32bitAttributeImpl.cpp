//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include <boost/endian/conversion.hpp>
#include "zcl/exceptions/NoUintException.h"
#include "ZCLBitmap32bitAttributeImpl.h"

namespace zigbee {
    std::any ZCLBitmap32bitAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLBitmap32bitAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(std::bitset<32>)) {
            value = std::any_cast<std::bitset<32>>(anyValue);
        } else if (anyValue.type() == typeid(std::uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttributeImpl *attribute) {
        out << attribute->value.to_string();
        return out;
    }

    void ZCLBitmap32bitAttributeImpl::setRawValue(uint8_t *rawData) {
        value = boost::endian::little_to_native(*(uint32_t *) rawData);
    }


}