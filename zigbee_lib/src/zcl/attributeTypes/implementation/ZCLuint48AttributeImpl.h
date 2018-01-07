/*
 * ZCLuint8Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLUINT48ATTRIBUTE_IMPL_H_
#define ZCLUINT48ATTRIBUTE_IMPL_H_

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLuint48Attribute.h"

namespace zigbee {

    class ZCLUINT48AttributeImpl : public ZCLuint48Attribute, public ZCLAttributeImpl {
    public:
        ZCLUINT48AttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                              std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt48, name, readOnly) {
        }

        ~ZCLUINT48AttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        static std::string name() {
            return "UInt48";
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
        friend std::ostream &operator<<(std::ostream &out, const ZCLUINT48AttributeImpl *);

    protected:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint64_t value;
    };


} /* namespace zigbee */

#endif /* ZCLUINT8ATTRIBUTE_H_ */
