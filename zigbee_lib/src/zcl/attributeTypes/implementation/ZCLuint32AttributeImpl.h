/*
 * ZCLuint8Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLUINT32ATTRIBUTE_IMPL_H_
#define ZCLUINT32ATTRIBUTE_IMPL_H_

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLuint32Attribute.h"

namespace zigbee {

    class ZCLUINT32AttributeImpl : public ZCLuint32Attribute, public ZCLAttributeImpl {
    public:
        ZCLUINT32AttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                               std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt32, name, readOnly) {
        }

        ~ZCLUINT32AttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        static std::string name() {
            return "UInt32";
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

        friend std::ostream &operator<<(std::ostream &out, const ZCLUINT32AttributeImpl *);

    protected:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLUINT32AttributeImpl *);


} /* namespace zigbee */

#endif /* ZCLUINT8ATTRIBUTE_H_ */
