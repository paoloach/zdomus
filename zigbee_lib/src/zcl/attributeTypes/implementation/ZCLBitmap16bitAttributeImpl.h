//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_IMPL_H
#define ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_IMPL_H

#include <experimental/string_view>
#include <bitset>
#include <ostream>
#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLBitmap16bitAttribute.h"
#include "zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCLBitmap16bitAttributeImpl : public ZCLBitmap16bitAttribute, public ZCLAttributeImpl {
        union Converter {
            uint16_t value;
            uint8_t raw[2];
        };
    public:
        ZCLBitmap16bitAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                    std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLType16bitBitmap, name,
                                 readOnly) {}

        ~ZCLBitmap16bitAttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return boost::lexical_cast<std::string>(value);
        }

        void setValue(std::any &value) override;

        static std::string name() {
            return "16bitBitmap";
        }

        void setRawValue(uint8_t *rawData) override;

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

        friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttributeImpl *);


    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        std::bitset<16> value;
    };

}

#endif //ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
