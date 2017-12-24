/*
 * ZCLuint16Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLuint24ATTRIBUTE_H_
#define ZCLuint24ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_uint24_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt24> {
        union Converter {
            uint32_t value;
            uint8_t raw[4];
        };
    public:
        ZCL_uint24_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                             std::experimental::string_view name, bool readOnly);

    public:
        std::any getValue() const override;
        std::string getStrValue() const  override {
            return std::to_string(value);
        }

        virtual void sendValue(uint32_t newValue);

        static std::string name() {
            return "UInt24";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_uint24_Attribute *);

    private:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_uint24_Attribute *);

} /* namespace zigbee */

#endif /* ZCLuint16ATTRIBUTE_H_ */
