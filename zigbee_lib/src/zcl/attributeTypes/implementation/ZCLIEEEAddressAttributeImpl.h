/*
 * ZCLIEEEAddressAttribute.h
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLIEEEADDRESSATTRIBUTE_IMPL_H_
#define ZCLIEEEADDRESSATTRIBUTE_IMPL_H_

#include "zcl/attributeTypes/ZCLIEEEAddressAttribute.h"
#include "src/zcl/impl/ZCLAttributeImpl.h"

namespace zigbee {

    class ZCLIEEEAddressAttributeImpl : public ZCLIEEEAddressAttribute, public ZCLAttributeImpl {
    private:
        union Value {
            uint64_t data;
            uint8_t raw[8];
        };
    public:
        ZCLIEEEAddressAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent,
                                    ZigbeeClusterId identifier, std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeIEEEaddress, name,
                                 readOnly) {
        }

        ~ZCLIEEEAddressAttributeImpl() override = default;


    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value.data);
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        const uint8_t *getRawValue() const { return value.raw; }
        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }
    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        Value value;
    };

} /* namespace zigbee */

#endif /* ZCLIEEEADDRESSATTRIBUTE_H_ */
