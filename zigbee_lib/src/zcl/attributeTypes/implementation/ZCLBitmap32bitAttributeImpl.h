//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_IMPL_H
#define ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_IMPL_H

#include <bitset>
#include <ostream>
#include "zcl/attributeTypes/ZCLBitmap32bitAttribute.h"
#include "src/zcl/impl/ZCLAttributeImpl.h"

namespace zigbee {
    class ZCLBitmap32bitAttributeImpl : public ZCLBitmap32bitAttribute, public ZCLAttributeImpl {
    public:
        ZCLBitmap32bitAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent,
                                    ZigbeeClusterId identifier, std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLType32bitBitmap, name,
                                 readOnly) {}

        ~ZCLBitmap32bitAttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return boost::lexical_cast<std::string>(value);
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

    private:
        friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttributeImpl *);

    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        std::bitset<32> value;
    };
}


#endif //ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H
