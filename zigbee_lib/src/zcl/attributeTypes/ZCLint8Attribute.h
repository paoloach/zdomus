//
// Created by developer on 11/26/15.
//

#ifndef ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {
    class ZCLint8Attribute : public ZCLAttribute {
    public:
        ZCLint8Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier, const std::string &name, bool readOnly);
    public:
        virtual boost::any getValue() const override;
        virtual void sendValue(int8_t newValue);
        static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeSInt8;
        static std::string name() {
            return "Int8";
        }
    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);
        friend std::ostream &operator<<(std::ostream &out, const ZCLint8Attribute *);
    protected:
        uint32_t value;
    };


}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H