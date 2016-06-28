//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#include <boost/endian/conversion.hpp>
#include "ZCLBitmap32bitAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCLBitmap32bitAttribute::ZCLBitmap32bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                                     ZigbeeClusterId identifier, std::experimental::string_view name,
                                                     bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLType32bitBitmap>(zigbeeDevice, parent, identifier, name, readOnly){
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
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
        value = boost::endian::little_to_native( *(uint32_t *) rawData->data);
    }

    std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttribute *attribute) {
        out << attribute->value.to_string();
        return out;
    }

    void ZCLBitmap32bitAttribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(uint32_t *) rawData);
    }


}