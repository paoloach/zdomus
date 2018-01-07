//
// Created by developer on 11/26/15.
//

#include "ZCLint16AttributeImpl.h"
#include "zcl/exceptions/NoInt32Exception.h"

namespace zigbee {

    std::any ZCLint16AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLint16AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(int32_t)) {
            value = std::any_cast<int32_t>(anyValue);
        } else {
            throw NoInt32Exception(anyValue);
        }
        if (value > 0xFFFF) {
            throw std::out_of_range("value exceeded 8 bits");
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLint16AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLint16AttributeImpl::setRawValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(int16_t *) rawData);
    }


}