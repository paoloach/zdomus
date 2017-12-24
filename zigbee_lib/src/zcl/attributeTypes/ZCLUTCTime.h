//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLUTCTIME_H
#define ZIGBEE_LIB_ZCLUTCTIME_H

#include "../ZCLAttribute.h"

namespace zigbee {


    class ZCLUTCTime : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUTCTime> {
        union Converter {
            uint32_t value;
            uint8_t raw[4];
        };
    public:
        ZCLUTCTime(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                   std::experimental::string_view name, bool readOnly);

        ~ZCLUTCTime() override = default;
    public:
        std::any getValue() const override;

        std::string getStrValue() const  override {
            return std::to_string(value);
        }

        virtual void sendValue(uint32_t newValue);

        static std::string name() {
            return "UTCTime";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)  override ;

        void internalSetValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLUTCTime *);

    private:
        uint32_t value;
    };

}

#endif //ZIGBEE_LIB_ZCLUTCTIME_H
