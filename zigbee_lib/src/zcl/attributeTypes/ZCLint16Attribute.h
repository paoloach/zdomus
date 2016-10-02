/*
 * ZCLuint16Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLint16ATTRIBUTE_H_
#define ZCLint16ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_int16_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeSInt16> {
    public:
        ZCL_int16_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                            ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        boost::any getValue() const override;
        std::string getStrValue() const  override {
            return std::to_string(value);
        }

        virtual void sendValue(int16_t newValue);

        static std::string name() {
            return "Int16";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_int16_Attribute *);

    private:
        int32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_int16_Attribute *);


} /* namespace zigbee */

#endif /* ZCLint16ATTRIBUTE_H_ */
