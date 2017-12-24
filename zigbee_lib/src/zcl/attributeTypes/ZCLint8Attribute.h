//
// Created by developer on 11/26/15.
//

#ifndef ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {
    class ZCLint8Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeSInt8> {
    public:
        ZCLint8Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                         std::experimental::string_view name, bool readOnly);

    public:
        std::any getValue() const override;
        std::string getStrValue() const  override {
            return std::to_string(value);
        }

        virtual void sendValue(int8_t newValue);

        static std::string name() {
            return "Int8";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCLint8Attribute *);

    protected:
        uint32_t value;
    };


}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
