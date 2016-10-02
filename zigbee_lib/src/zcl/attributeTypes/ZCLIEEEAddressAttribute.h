/*
 * ZCLIEEEAddressAttribute.h
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLIEEEADDRESSATTRIBUTE_H_
#define ZCLIEEEADDRESSATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCLIEEEAddressAttribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeIEEEaddress> {
    private:
        union Value {
            uint64_t data;
            uint8_t raw[8];
        };
    public:
        ZCLIEEEAddressAttribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

        virtual ~ZCLIEEEAddressAttribute();

    public:
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const  override  {
            return boost::lexical_cast<std::string>(value.data);
        }

        virtual const uint8_t *getRawValue() const;

        virtual void sendValue(uint64_t value);

        static std::string name() {
            return "IEEEAddress";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        virtual void internalSetValue(uint8_t * rawData) override;

    private:
        Value value;
    };

} /* namespace zigbee */

#endif /* ZCLIEEEADDRESSATTRIBUTE_H_ */
