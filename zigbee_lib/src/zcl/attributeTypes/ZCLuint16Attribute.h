/*
 * ZCLuint16Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLuint16ATTRIBUTE_H_
#define ZCLuint16ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_uint16_Attribute : public ZCLAttribute {
    public:
        ZCL_uint16_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                             ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

    public:
        virtual boost::any getValue() const override;

        virtual void sendValue(uint16_t newValue);

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUInt16;

        static std::string name() {
            return "UInt16";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);

        friend std::ostream &operator<<(std::ostream &out, const ZCL_uint16_Attribute *);

    private:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_uint16_Attribute *);


} /* namespace zigbee */

#endif /* ZCLuint16ATTRIBUTE_H_ */
