//
// Created by Paolo Achdjian on 11/19/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_uint32_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt32> {
    public:
        ZCL_uint32_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                             std::experimental::string_view name, bool readOnly);

    public:
        boost::any getValue() const override;
        std::string getStrValue() const  override {
            return std::to_string(value);
        }

        virtual void sendValue(uint32_t newValue);

        static std::string name() {
            return "UInt32";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) override;

        void internalSetValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_uint32_Attribute *);

    private:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_uint32_Attribute *);

} /* namespace zigbee */

#endif //ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H
