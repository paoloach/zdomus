/*
 * ZCLuint8Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLUINT8ATTRIBUTE_H_
#define ZCLUINT8ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_uint8_Attribute : public ZCLAttribute {
    public:
        ZCL_uint8_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,  std::experimental::string_view   name, bool readOnly);
    public:
        virtual boost::any getValue() const override;
        virtual void sendValue(uint8_t newValue);
        static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeUInt8;
        static std::string name() {
            return "UInt8";
        }
    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);
        friend std::ostream &operator<<(std::ostream &out, const ZCL_uint8_Attribute *);
    protected:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_uint8_Attribute *);


} /* namespace zigbee */

#endif /* ZCLUINT8ATTRIBUTE_H_ */
