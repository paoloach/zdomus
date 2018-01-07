/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint24AttributeImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    std::any ZCLUINT24AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLUINT24AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
        if (value > 0xFFFFFF) {
            throw std::out_of_range("value exceeded 24 bits");
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLUINT24AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLUINT24AttributeImpl::setRawValue(uint8_t *rawData) {
        union Converter {
            uint32_t value;
            uint8_t raw[4];
        };
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        converter.raw[2] = *(rawData + 2);
        converter.raw[3] = 0;
        value = boost::endian::little_to_native(converter.value);
    }


} /* namespace zigbee */
