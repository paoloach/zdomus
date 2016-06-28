/*
 * ZCLenum8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLENUM8BITATTRIBUTE_H_
#define ZCLENUM8BITATTRIBUTE_H_

#include "ZCLuint8Attribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_enum8bit_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeenum8> {
    public:
        ZCL_enum8bit_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                               std::experimental::string_view name, bool readOnly);

        virtual ~ZCL_enum8bit_Attribute();

    public:
        virtual void sendValue(uint8_t newValue);
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const {
            return boost::lexical_cast<std::string>(value);
        }

        static std::string name() {
            return "8BitEnum";
        }

        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) override {
            value = *rawData->data;
        }

        virtual void internalSetValue(uint8_t*rawData) override {
            value =  *rawData;
        }


        friend std::ostream &operator<<(std::ostream &out, const ZCL_enum8bit_Attribute *);

    private:

        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_enum8bit_Attribute *);

} /* namespace zigbee */

#endif /* ZCLENUM8BITATTRIBUTE_H_ */
