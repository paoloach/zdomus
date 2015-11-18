//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLUTCTIME_H
#define ZIGBEE_LIB_ZCLUTCTIME_H

#include "../ZCLAttribute.h"

namespace zigbee {


class ZCLUTCTime  : public ZCLAttribute {
    union Converter {
        uint32_t value;
        uint8_t raw[4];
    };
public:
    ZCLUTCTime(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
    virtual ~ZCLUTCTime(){};
public:
    virtual  boost::any getValue() const override;
    virtual void sendValue(uint32_t newValue);
    static ZCLTypeDataType type(){
        return ZCLTypeDataType::ZCLTypeUTCTime;
    }
    static std::string name() {
        return "UTCTime";
    }
private:
    virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);
    friend std::ostream & operator<<(std::ostream & out, const ZCLUTCTime *);
private:
    uint32_t value;
};

}

#endif //ZIGBEE_LIB_ZCLUTCTIME_H
