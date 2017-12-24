/*
 * ZCLIEEEAddressAttribute.cpp
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#include <ios>

#include "ZCLIEEEAddressAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCLIEEEAddressAttribute::ZCLIEEEAddressAttribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                                     ZigbeeClusterId identifier, std::experimental::string_view name,
                                                     bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeIEEEaddress>(zigbeeDevice, parent, identifier, name, readOnly) {
    }

    ZCLIEEEAddressAttribute::~ZCLIEEEAddressAttribute() = default;

    std::any ZCLIEEEAddressAttribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value.data);
    }

    void ZCLIEEEAddressAttribute::sendValue(uint64_t newValue) {
        sendValueToDevice(8, (uint8_t *) &newValue);
    }

    void ZCLIEEEAddressAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        std::copy( std::begin(rawData->data),std::begin(rawData->data)+8,std::begin(value.raw));
    }

    const uint8_t *ZCLIEEEAddressAttribute::getRawValue() const {
        return value.raw;
    }

    void ZCLIEEEAddressAttribute::internalSetValue(uint8_t *rawData) {
        memcpy(value.raw,rawData,8);
    }


    std::ostream &operator<<(std::ostream &out, const ZCLIEEEAddressAttribute *attribute) {
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
