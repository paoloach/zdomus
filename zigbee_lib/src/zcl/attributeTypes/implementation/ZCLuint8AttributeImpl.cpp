/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint8AttributeImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    std::any ZCLUINT8AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLUINT8AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
        if (value > 0xFF) {
            throw std::out_of_range("value exceeded 8 bits");
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLUINT8AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLUINT8AttributeImpl::setRawValue(uint8_t *rawData) {
        value = *rawData;
    }


} /* namespace zigbee */
