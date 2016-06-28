//
// Created by Paolo Achdjian on 11/20/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H

#include <experimental/string_view>
#include <bitset>
#include <ostream>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCLBitmap16bitAttribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLType16bitBitmap> {
        union Converter {
            uint16_t value;
            uint8_t raw[2];
        };
    public:
        ZCLBitmap16bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;

        virtual std::string getStrValue() const {
            return boost::lexical_cast<std::string>(value);
        }

        virtual void sendValue(std::bitset<16> value);

        virtual bool getValue(int bitIndex) const;

        static std::string name() {
            return "16bitBitmap";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) override;

        virtual void internalSetValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap16bitAttribute *);


    private:
        std::bitset<16> value;
    };

}

#endif //ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
