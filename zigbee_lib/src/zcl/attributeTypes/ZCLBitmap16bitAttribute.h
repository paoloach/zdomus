//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H

#include <bitset>
#include <ostream>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCLBitmap16bitAttribute : public ZCLAttribute {
    union Converter {
        uint16_t value;
        uint8_t raw[2];
    };
public:
    ZCLBitmap16bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier, const std::string &name, bool readOnly);

public:
    virtual boost::any getValue() const override;

    virtual void sendValue(std::bitset<16> value);

    virtual bool getValue(int bitIndex) const;
    static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLType16bitBitmap;
    static std::string name() {
        return "16bitBitmap";
    }

private:
    virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);

    friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttribute *);

private:
    std::bitset<16> value;
};

}

#endif //ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
