//
// Created by Paolo Achdjian on 11/19/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLINT32ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT32ATTRIBUTE_H


#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_int32_Attribute : public ZCLAttribute {
        union Converter {
            int32_t value;
            uint8_t raw[4];
        };
    public:
        ZCL_int32_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                            ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;

        virtual void sendValue(int32_t newValue);

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeSInt32;

        static std::string name() {
            return "Int32";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);

        friend std::ostream &operator<<(std::ostream &out, const ZCL_int32_Attribute *);

    private:
        int32_t value;
    };

}

#endif //ZIGBEE_LIB_ZCLINT32ATTRIBUTE_H
