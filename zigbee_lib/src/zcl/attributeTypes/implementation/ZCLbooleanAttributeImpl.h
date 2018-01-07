/*
 * ZCLbooleanAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBOOLEANATTRIBUTE_IMPL_H_
#define ZCLBOOLEANATTRIBUTE_IMPL_H_

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLBooleanAttribute.h"

namespace zigbee {

    class ZCLBooleanAttributeImpl : public  ZCLBooleanAttribute, public ZCLAttributeImpl {
    public:
        ZCLBooleanAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent,
                              ZigbeeClusterId identifier, std::string_view name, bool readOnly):
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, type, name,
                                 readOnly) {}

        ~ZCLBooleanAttributeImpl() override=default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return boost::lexical_cast<std::string>(value);
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
        friend std::ostream &operator<<(std::ostream &out, const ZCLBooleanAttributeImpl *);

    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        bool value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLBooleanAttributeImpl *);

} /* namespace zigbee */

#endif /* ZCLBOOLEANATTRIBUTE_H_ */
