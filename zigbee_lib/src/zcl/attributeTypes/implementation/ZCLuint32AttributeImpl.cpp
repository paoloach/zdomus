/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint32AttributeImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    std::any ZCLUINT32AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLUINT32AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLUINT32AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLUINT32AttributeImpl::setRawValue(uint8_t *rawData) {
        value = boost::endian::little_to_native(*(uint32_t *) rawData);
    }


} /* namespace zigbee */
