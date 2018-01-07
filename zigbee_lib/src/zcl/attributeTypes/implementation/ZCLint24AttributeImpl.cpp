//
// Created by developer on 11/26/15.
//

#include "ZCLint24AttributeImpl.h"
#include "zcl/exceptions/NoInt32Exception.h"

namespace zigbee {

    std::any ZCLint24AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLint24AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(int32_t)) {
            value = std::any_cast<int32_t>(anyValue);
        } else {
            throw NoInt32Exception(anyValue);
        }
        if (value > 0xFFFF) {
            throw std::out_of_range("value exceeded 8 bits");
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLint24AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLint24AttributeImpl::setRawValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        converter.raw[2] = *(rawData + 2);
        if (converter.raw[2] & 0x80) {
            converter.raw[3] = 0xFF;
        } else {
            converter.raw[3] = 0;
        }
        value = boost::endian::little_to_native(converter.value);
    }


}