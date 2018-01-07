/*
 * ZCLenum8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLENUM8BITATTRIBUTE_IMPL_H_
#define ZCLENUM8BITATTRIBUTE_IMPL_H_

#include "ZCLuint8AttributeImpl.h"
#include "src/zigbee/AttributeStatusRecord.h"
#include "zcl/attributeTypes/ZCLEnum8bitAttribute.h"

namespace zigbee {

    class ZCLEnum8bitAttributeImpl : public ZCLEnum8bitAttribute, public ZCLAttributeImpl {
    public:
        ZCLEnum8bitAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                 std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeenum8, name, readOnly) {
        }

        ~ZCLEnum8bitAttributeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
        friend std::ostream &operator<<(std::ostream &out, const ZCLEnum8bitAttributeImpl *);

    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLEnum8bitAttributeImpl *);

} /* namespace zigbee */

#endif /* ZCLENUM8BITATTRIBUTE_H_ */
