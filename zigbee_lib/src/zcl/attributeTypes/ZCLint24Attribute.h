//
// Created by developer on 11/16/15.
//

#ifndef ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCLint24Attribute : public ZCLAttribute {
        union Converter {
            uint32_t value;
            uint8_t raw[4];
        };
    public:
        ZCLint24Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                          ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;

        virtual void sendValue(uint32_t newValue);

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeSInt24;

        static std::string name() {
            return "Int24";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);

        friend std::ostream &operator<<(std::ostream &out, const ZCLint24Attribute *);

    private:
        int32_t value;
    };


}

#endif //ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H
