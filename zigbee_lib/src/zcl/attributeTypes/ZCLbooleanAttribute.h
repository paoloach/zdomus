/*
 * ZCLbooleanAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBOOLEANATTRIBUTE_H_
#define ZCLBOOLEANATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_boolean_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeBool> {
    public:
        ZCL_boolean_Attribute(ZigbeeDevice *zigbeeDevice, Cluster *parent,
                              ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly);

        ~ZCL_boolean_Attribute() override;

    public:
        boost::any getValue() const override;

        std::string getStrValue() const override {
            return boost::lexical_cast<std::string>(value);
        }

        virtual void sendValue(bool value);

        static std::string name() {
            return "Boolean";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) override;

        void internalSetValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_boolean_Attribute *);

    private:
        bool value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_boolean_Attribute *);

} /* namespace zigbee */

#endif /* ZCLBOOLEANATTRIBUTE_H_ */
