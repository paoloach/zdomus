//
// Created by developer on 11/16/15.
//

#ifndef ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCLint24Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeSInt24> {
        union Converter {
            uint32_t value;
            uint8_t raw[4];
        };
    public:
        ZCLint24Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                          ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        boost::any getValue() const override;
        std::string getStrValue() const   override {
            return std::to_string(value);
        }

        virtual void sendValue(uint32_t newValue);

        static std::string name() {
            return "Int24";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLint24Attribute *);

    private:
        int32_t value;
    };


}

#endif //ZIGBEE_LIB_ZCLINT24ATTRIBUTE_H
