//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include "ZCLBitmap32bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCLBitmap32bitAttribute::ZCLBitmap32bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier, const std::string &name, bool readOnly) :
        ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLType32bitBitmap, name, readOnly) {
    if (zigbeeDevice) {
        zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
                                                [this](std::shared_ptr<AttributeStatusRecord> rawData){setValue(rawData);});
    }
}

boost::any ZCLBitmap32bitAttribute::getValue() const {
    if (status != Available) {
        throw ZCLAttributeNotAvailableException(parent, identifier);
    }
    return boost::any(value);
}

bool ZCLBitmap32bitAttribute::getValue(int index) const {
    if (status != Available) {
        throw ZCLAttributeNotAvailableException(parent, identifier);
    }
    return value[index];
}

void ZCLBitmap32bitAttribute::sendValue(std::bitset<32> value) {
    auto toSend = value.to_ulong();
    sendValueToDevice(4, (uint8_t *) &toSend);
}

void ZCLBitmap32bitAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
    Converter converter;
    converter.raw[0] = *rawData->data;
    converter.raw[1] = *(rawData->data + 1);
    converter.raw[2] = *(rawData->data + 2);
    converter.raw[3] = *(rawData->data + 3);
    value = converter.value;
}

std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttribute *attribute) {
    out << attribute->value.to_string();
    return out;
}
}