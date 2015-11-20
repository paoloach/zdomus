//
// Created by developer on 11/16/15.
//

#include "ZCLint24Attribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCLint24Attribute::ZCLint24Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
        ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeSInt24, name, readOnly) {
    if (zigbeeDevice) {
        zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
                                                boost::bind(&ZCLint24Attribute::setValue, this, _1));
    }
}

boost::any ZCLint24Attribute::getValue() const {
    if (status != Available) {
        throw ZCLAttributeNotAvailableException(parent, identifier);
    }
    return boost::any(value);
}

void ZCLint24Attribute::sendValue(uint32_t newValue) {
    sendValueToDevice(3, (uint8_t *) &newValue);
}

void ZCLint24Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
    Converter converter;
    converter.raw[0] = *rawData->data;
    converter.raw[1] = *(rawData->data + 1);
    converter.raw[2] = *(rawData->data + 2);
    if (converter.raw[2] & 0x80){
        converter.raw[3] = 0xFF;
    } else {
        converter.raw[3] = 0;
    }
    value = converter.value;
}

std::ostream & operator<<(std::ostream & out, const ZCLint24Attribute * attribute) {
    out << attribute->value;
    return out;
}

} /* namespace zigbee */