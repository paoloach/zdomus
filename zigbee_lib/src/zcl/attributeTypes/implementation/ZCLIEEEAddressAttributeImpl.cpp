/*
 * ZCLIEEEAddressAttribute.cpp
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLIEEEAddressAttributeImpl.h"
#include "zcl/exceptions/NoUInt64Exception.h"

namespace zigbee {

    std::any ZCLIEEEAddressAttributeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value.data);
    }

    void ZCLIEEEAddressAttributeImpl::setValue(std::any &anyValue) {
        if (anyValue.type() == typeid(uint64_t)) {
            value.data = std::any_cast<uint64_t>(anyValue);
        } else {
            throw NoUInt64Exception(anyValue);
        }
    }


    void ZCLIEEEAddressAttributeImpl::setRawValue(uint8_t *rawData) {
        memcpy(value.raw,rawData,8);
    }


    std::ostream &operator<<(std::ostream &out, const ZCLIEEEAddressAttributeImpl *attribute) {
        const uint8_t *ieeeAddress = attribute->getRawValue();
        out.fill('0');
        out.width(2);
        for (int i = 7; i > 0; i--) {
            out << std::hex << ieeeAddress[i] << " - ";
        }
        out << std::hex << ieeeAddress[0];
        return out;
    }

} /* namespace zigbee */
