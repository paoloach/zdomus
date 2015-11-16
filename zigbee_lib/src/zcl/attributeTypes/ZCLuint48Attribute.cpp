//
// Created by developer on 11/16/15.
//

#include "ZCLuint48Attribute.h"
#include "../Cluster.h"

namespace  zigbee {


    ZCLuint48Attribute::ZCLuint48Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                           ZigbeeClusterId identifier, const std::string &name, bool readOnly) :
            ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt48, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    boost::bind(&ZCLuint48Attribute::setValue, this, _1));
        }

    }

    boost::any ZCLuint48Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCLuint48Attribute::sendValue(uint64_t newValue) {
        sendValueToDevice(6, (uint8_t *) &newValue);
    }

    void ZCLuint48Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        Converter converter;
        converter.raw[0] = *rawData->data;
        converter.raw[1] = *(rawData->data + 1);
        converter.raw[2] = *(rawData->data + 2);
        converter.raw[3] = *(rawData->data + 3);
        converter.raw[4] = *(rawData->data + 4);
        converter.raw[5] = *(rawData->data + 5);
        converter.raw[6] = 0;
        converter.raw[7] = 0;
        value = converter.value;
    }

    std::ostream & operator<<(std::ostream &out, const ZCLuint48Attribute *attribute) {
        out << attribute->value;
        return out;
    }
};