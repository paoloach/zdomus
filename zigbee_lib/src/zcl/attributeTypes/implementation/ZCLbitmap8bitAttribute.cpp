/*
 * ZCLbitmap8bitAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include <stdexcept>
#include "src/zcl/attributeTypes/implementation/ZCLbitmap8bitAttribute.h"
#include "src/zcl/impl/ClusterImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    std::any ZCLBitmap8bitAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }


    std::ostream &operator<<(std::ostream &out, const ZCLBitmap8bitAttributeImpl *attribute) {
        int bitmask = 0x80;
        int value = attribute->value;
        for (int i = 0; i < 7; i++) {
            if (value & bitmask) {
                out << '1';
            } else {
                out << '0';
            }
            out << '-';
            bitmask >>= 1;
        }
        if (value & 0x1) {
            out << '1';
        } else {
            out << '0';
        }
        return out;
    }

    void ZCLBitmap8bitAttributeImpl::setRawValue(uint8_t *rawData) {
        value = *rawData;
    }

    void ZCLBitmap8bitAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)){
            value = std::any_cast<uint32_t >(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
        if (value > 0xFF){
            throw std::out_of_range("value exceeded 8 bits");
        }
    }


} /* namespace zigbee */
