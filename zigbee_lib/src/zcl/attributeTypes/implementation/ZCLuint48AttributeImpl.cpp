/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint48AttributeImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {
    union Converter48 {
        uint64_t value;
        uint8_t raw[8];
    };
    std::any ZCLUINT48AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLUINT48AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint64_t)) {
            value = std::any_cast<uint64_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLUINT48AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLUINT48AttributeImpl::setRawValue(uint8_t *rawData) {
        Converter48 converter;
        std::copy(rawData, rawData+6, std::begin(converter.raw));
        converter.raw[6] = 0;
        converter.raw[7] = 0;
        value = boost::endian::little_to_native(converter.value);
    }


} /* namespace zigbee */
