/*
 * ZCLuint8Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLUINT8ATTRIBUTE_H_
#define ZCLUINT8ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_uint8_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt8> {
    public:
        ZCL_uint8_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                            std::experimental::string_view name, bool readOnly);

    public:
        boost::any getValue() const override;
        std::string getStrValue() const override {
            return std::to_string(value);
        }

        virtual void sendValue(uint8_t newValue);

        static std::string name() {
            return "UInt8";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_uint8_Attribute *);

    protected:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_uint8_Attribute *);


} /* namespace zigbee */

#endif /* ZCLUINT8ATTRIBUTE_H_ */
