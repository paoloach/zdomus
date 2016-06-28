//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H

#include <bitset>
#include <ostream>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {
    class ZCLBitmap32bitAttribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLType32bitBitmap> {
    public:
        ZCLBitmap32bitAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const {
            return boost::lexical_cast<std::string>(value);
        }

        virtual void sendValue(std::bitset<32> value);

        virtual bool getValue(int bitIndex) const;

        static std::string name() {
            return "32bitBitmap";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;
        virtual void internalSetValue(uint8_t * rawData) override ;

        friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap32bitAttribute *);

    private:
        std::bitset<32> value;
    };
}


#endif //ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H
