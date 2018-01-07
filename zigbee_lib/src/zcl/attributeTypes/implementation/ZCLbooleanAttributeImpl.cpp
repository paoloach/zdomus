/*
 * ZCLbooleanAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include <src/zcl/exceptions/NoBoolException.h>
#include "ZCLbooleanAttributeImpl.h"
#include "src/zcl/impl/ClusterImpl.h"

namespace zigbee {

    std::any ZCLBooleanAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLBooleanAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(bool)) {
            value = std::any_cast<bool>(anyValue);
        } else {
            throw NoBoolException(anyValue);
        }
    }


    std::ostream &operator<<(std::ostream &out, const ZCLBooleanAttributeImpl *attribute) {
        out << (attribute->value ? "true" : "false");
        return out;
    }

    void ZCLBooleanAttributeImpl::setRawValue(uint8_t *rawData) {
        value = *rawData;
    }


} /* namespace zigbee */
