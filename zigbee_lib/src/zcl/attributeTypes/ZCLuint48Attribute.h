//
// Created by developer on 11/16/15.
//

#ifndef ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H

#include "../ZCLAttribute.h"

namespace zigbee {


    class ZCLuint48Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt48> {
        union Converter {
            uint64_t value;
            uint8_t raw[8];
        };
    public:
        ZCLuint48Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                           std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const  override {
            return boost::lexical_cast<std::string>(value);
        }

        virtual void sendValue(uint64_t newValue);

        static std::string name() {
            return "UInt48";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)  override ;

        virtual void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLuint48Attribute *);

    private:
        uint64_t value;

    };

} /* namespace zigbee */

#endif //ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
