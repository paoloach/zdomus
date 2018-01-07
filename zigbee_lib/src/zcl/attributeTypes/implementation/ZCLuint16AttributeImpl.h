/*
 * ZCLuint8Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLUINT16ATTRIBUTE_IMPL_H_
#define ZCLUINT16ATTRIBUTE_IMPL_H_

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLuint16Attribute.h"

namespace zigbee {

    class ZCLUINT16AttributeImpl : public ZCLuint16Attribute, public ZCLAttributeImpl {
    public:
        ZCLUINT16AttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                               std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, type, name, readOnly) {
        }

        ~ZCLUINT16AttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        static std::string name() {
            return "UInt16";
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLUINT16AttributeImpl *);

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

    protected:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLUINT16AttributeImpl *);


} /* namespace zigbee */

#endif /* ZCLUINT8ATTRIBUTE_H_ */
