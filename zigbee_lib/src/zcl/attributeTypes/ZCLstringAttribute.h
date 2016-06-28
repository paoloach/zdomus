/*
 * ZCLstringAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLSTRINGATTRIBUTE_H_
#define ZCLSTRINGATTRIBUTE_H_

#include <string>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_string_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeStringChar> {
    public:
        ZCL_string_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                             ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const {
            return value;
        }

        virtual void sendValue(const std::string &newValue);

        static std::string name() {
            return "String";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;
        virtual void internalSetValue(uint8_t * rawData) override ;

        ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeStringChar> zclAttributeRawValueImpl;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_string_Attribute *);

    private:
        std::string value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_string_Attribute *);

} /* namespace zigbee */

#endif /* ZCLSTRINGATTRIBUTE_H_ */
