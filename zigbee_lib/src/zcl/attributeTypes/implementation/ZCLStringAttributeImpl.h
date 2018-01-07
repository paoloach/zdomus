/*
 * ZCLstringAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLSTRINGATTRIBUTE_IMPL_H_
#define ZCLSTRINGATTRIBUTE_IMPL_H_

#include <string>
#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLStringAttribute.h"

namespace zigbee {

    class ZCLStringAttributeImpl : public ZCLStringAttribute, public ZCLAttributeImpl {
    public:
        ZCLStringAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                               std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, type, name, readOnly) {
        }

        ~ZCLStringAttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return value;
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLStringAttributeImpl *);
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        std::string value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLStringAttributeImpl *);

} /* namespace zigbee */

#endif /* ZCLSTRINGATTRIBUTE_H_ */
