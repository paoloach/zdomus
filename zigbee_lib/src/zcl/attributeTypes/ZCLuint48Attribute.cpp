//
// Created by developer on 11/16/15.
//

#include "ZCLuint48Attribute.h"
#include "../Cluster.h"

namespace zigbee {


    ZCLuint48Attribute::ZCLuint48Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                           ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt48>(zigbeeDevice, parent, identifier, name, readOnly) {

    }

    std::any ZCLuint48Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLuint48Attribute::sendValue(uint64_t newValue) {
        sendValueToDevice(6, (uint8_t *) &newValue);
    }

    void ZCLuint48Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        Converter converter;
        std::copy(rawData->data.begin(), rawData->data.begin()+6, std::begin(converter.raw));
        converter.raw[6] = 0;
        converter.raw[7] = 0;
        value = converter.value;
    }

    std::ostream &operator<<(std::ostream &out, const ZCLuint48Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCLuint48Attribute::internalSetValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        converter.raw[2] = *(rawData + 2);
        converter.raw[3] = *(rawData + 3);
        converter.raw[4] = *(rawData + 4);
        converter.raw[5] = *(rawData + 5);
        converter.raw[6] = 0;
        converter.raw[7] = 0;
        value = converter.value;
    }


};