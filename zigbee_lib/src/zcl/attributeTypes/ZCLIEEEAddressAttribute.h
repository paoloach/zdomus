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
        ZCLIEEEAddressAttribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

        ~ZCLIEEEAddressAttribute() override;

    public:
        std::any getValue() const override;
        std::string getStrValue() const  override  {
            return std::to_string(value.data);
        }

        virtual const uint8_t *getRawValue() const;

        virtual void sendValue(uint64_t value);

        static std::string name() {
            return "IEEEAddress";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;

        void internalSetValue(uint8_t * rawData) override;

    private:
        Value value;
    };

} /* namespace zigbee */

#endif /* ZCLIEEEADDRESSATTRIBUTE_H_ */
