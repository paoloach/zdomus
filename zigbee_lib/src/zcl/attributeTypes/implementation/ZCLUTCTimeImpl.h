//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLUTCTIME_IMPL_H
#define ZIGBEE_LIB_ZCLUTCTIME_IMPL_H

#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLUTCTime.h"

namespace zigbee {
    class ZCLUTCTimeImpl : public ZCLUTCTime, public ZCLAttributeImpl {
    public:
        ZCLUTCTimeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                       std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUTCTime, name, readOnly) {
        }

        ~ZCLUTCTimeImpl() override = default;

    public:
        std::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        static std::string name() {
            return "UTCTime";
        }

        void setValue(std::any &value) override;

        void setRawValue(uint8_t *rawData) override;

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

        friend std::ostream &operator<<(std::ostream &out, const ZCLUTCTimeImpl *);

    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint32_t value;
    };

}

#endif //ZIGBEE_LIB_ZCLUTCTIME_H
