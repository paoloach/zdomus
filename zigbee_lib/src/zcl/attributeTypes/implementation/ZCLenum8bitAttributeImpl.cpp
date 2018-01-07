/*
 * ZCLenum8bitAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "zcl/attributeTypes/implementation/ZCLenum8bitAttributeImpl.h"

#include "src/zcl/impl/ClusterImpl.h"
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {


    std::ostream &operator<<(std::ostream &out, const ZCLEnum8bitAttributeImpl *attribute) {
        out << attribute->value;
        return out;
    }

    std::any ZCLEnum8bitAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLEnum8bitAttributeImpl::setRawValue(uint8_t *rawData) {
        value = *rawData;
    }

    void ZCLEnum8bitAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
        if (value > 0xFF) {
            throw std::out_of_range("value exceeded 8 bits");
        }
    }

} /* namespace zigbee */
