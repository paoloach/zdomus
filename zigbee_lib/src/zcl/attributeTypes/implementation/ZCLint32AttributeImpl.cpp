//
// Created by developer on 11/26/15.
//

#include "ZCLint32AttributeImpl.h"
#include "zcl/exceptions/NoInt32Exception.h"

namespace zigbee {

    std::any ZCLint32AttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLint32AttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(int32_t)) {
            value = std::any_cast<int32_t>(anyValue);
        } else {
            throw NoInt32Exception(anyValue);
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLint32AttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLint32AttributeImpl::setRawValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(int32_t *) rawData);
    }


}