//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include "ZCLBitmap16bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCLBitmap16bitAttribute::ZCLBitmap16bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier, const std::string &name, bool readOnly) :
        ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLType16bitBitmap, name, readOnly) {
    if (zigbeeDevice) {
        zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
                                                [this](std::shared_ptr<AttributeStatusRecord> rawData){setValue(rawData);});
    }
}

boost::any ZCLBitmap16bitAttribute::getValue() const {
    if (status != Available) {
        throw ZCLAttributeNotAvailableException(parent, identifier);
    }
    return boost::any(value);
}

bool ZCLBitmap16bitAttribute::getValue(int index) const {
    if (status != Available) {
        throw ZCLAttributeNotAvailableException(parent, identifier);
    }
    return value[index];
}

void ZCLBitmap16bitAttribute::sendValue(std::bitset<16> value) {
    auto toSend = value.to_ulong();
    sendValueToDevice(2, (uint8_t *) &toSend);
}

void ZCLBitmap16bitAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
    Converter converter;
    converter.raw[0] = *rawData->data;
    converter.raw[1] = *(rawData->data + 1);
    value = converter.value;
}

std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttribute *attribute) {
    out << attribute->value.to_string();
    return out;
}
}