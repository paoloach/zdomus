//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLOCTETSTRING_IMPL_H
#define ZIGBEE_LIB_ZCLOCTETSTRING_IMPL_H

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLOctectString.h"

namespace zigbee {
    class ZCLOctetStringImpl : public ZCLOctetString, public ZCLAttributeImpl {
    public:
        ZCLOctetStringImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                           std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeStringOctect, name, readOnly) {
        }

        ~ZCLOctetStringImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override;

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLOctetStringImpl *);
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        std::vector<uint8_t> value;
    };
}


#endif //ZIGBEE_LIB_ZCLOCTETSTRING_H
