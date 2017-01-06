/*
 * ZCLbitmap8bitAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLbitmap8bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_bitmap8bit_Attribute::ZCL_bitmap8bit_Attribute(ZigbeeDevice *   zigbeeDevice, Cluster *parent,
                                                       ZigbeeClusterId identifier,
                                                       std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLType8bitBitmap>(zigbeeDevice, parent, identifier, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
        }
    }

    boost::any ZCL_bitmap8bit_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    bool ZCL_bitmap8bit_Attribute::getValue(int index) const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return (value & (1 << index)) != 0;
    }

    void ZCL_bitmap8bit_Attribute::sendValue(uint8_t newValue) {
        sendValueToDevice(1, &newValue);
    }

    void ZCL_bitmap8bit_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = *rawData->data;
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_bitmap8bit_Attribute *attribute) {
        int bitmask = 0x80;
        int value = attribute->value;
        for (int i = 0; i < 7; i++) {
            if (value & bitmask) {
                out << '1';
            } else {
                out << '0';
            }
            out << '-';
            bitmask >>= 1;
        }
        if (value & 0x1) {
            out << '1';
        } else {
            out << '0';
        }
        return out;
    }

    void ZCL_bitmap8bit_Attribute::internalSetValue(uint8_t *rawData) {
        value = *rawData;
    }


} /* namespace zigbee */
