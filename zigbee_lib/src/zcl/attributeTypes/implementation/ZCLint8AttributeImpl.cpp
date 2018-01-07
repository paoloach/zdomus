//
// Created by developer on 11/26/15.
//

#include "ZCLint8AttributeImpl.h"
#include "zcl/exceptions/NoInt32Exception.h"

namespace zigbee {

    std::any ZCLint8AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLint8AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(int32_t)) {
            value = std::any_cast<int32_t>(anyValue);
        } else {
            throw NoInt32Exception(anyValue);
        }
        if (value > 255 || value < 255) {
            throw std::out_of_range("value exceeded 8 bits");
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLint8AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLint8AttributeImpl::setRawValue(uint8_t *rawData) {
        value = *rawData;
    }


}