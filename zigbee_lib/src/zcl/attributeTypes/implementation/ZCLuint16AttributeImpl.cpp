/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint16AttributeImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    std::any ZCLUINT16AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLUINT16AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
        if (value > 0xFFFF) {
            throw std::out_of_range("value exceeded 16 bits");
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLUINT16AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLUINT16AttributeImpl::setRawValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(uint16_t *) rawData);
    }


} /* namespace zigbee */
