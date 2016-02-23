//
// Created by developer on 11/16/15.
//

#ifndef ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H

#include "../ZCLAttribute.h"

namespace zigbee {


class ZCLuint48Attribute : public ZCLAttribute {
    union Converter {
        uint64_t value;
        uint8_t raw[8];
    };
public:
    ZCLuint48Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);
public:
    virtual  boost::any getValue() const override;
    virtual void sendValue(uint64_t newValue);
    static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeUInt48;
    static std::string name() {
        return "UInt48";
    }
private:
    virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);
    friend std::ostream & operator<<(std::ostream & out, const ZCLuint48Attribute *);
private:
    uint64_t value;

};

} /* namespace zigbee */

#endif //ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
