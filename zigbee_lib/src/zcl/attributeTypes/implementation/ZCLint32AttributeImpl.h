//
// Created by developer on 11/26/15.
//

#ifndef ZIGBEE_LIB_ZCLINT32ATTRIBUTE_IMPL_H
#define ZIGBEE_LIB_ZCLINT32ATTRIBUTE_IMPL_H

#include "zcl/attributeTypes/ZCLint32Attribute.h"
#include "src/zcl/impl/ZCLAttributeImpl.h"

namespace zigbee {
    class ZCLint32AttributeImpl : public ZCLint32Attribute, public ZCLAttributeImpl {
    public:
        ZCLint32AttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                             std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeSInt32, name, readOnly) {
        }

        ~ZCLint32AttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
        friend std::ostream &operator<<(std::ostream &out, const ZCLint32AttributeImpl *);

    protected:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        int32_t value;
    };


}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
