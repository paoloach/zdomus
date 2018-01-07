/*
 * ZCLstringAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLStringAttributeImpl.h"
#include "zcl/exceptions/NoStringException.h"

namespace zigbee {


    std::any ZCLStringAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    std::ostream &operator<<(std::ostream &out, const ZCLStringAttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }


    void ZCLStringAttributeImpl::setValue(std::any &anyValue)  {
        if (anyValue.type() == typeid(std::string)) {
            value = std::any_cast<std::string>(anyValue);
        } else {
            throw NoStringException(anyValue);
        }
    }


    void ZCLStringAttributeImpl::setRawValue(uint8_t *rawData) {
        uint8_t len = *rawData;
        value = std::string();
        value.resize(len);
        for (int i = 0; i < len; i++) {
            value[i] = rawData[i + 1];
        }
        status = Available;
    }


} /* namespace zigbee */
