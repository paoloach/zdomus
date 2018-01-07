/*
 * ZCLbitmap8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBITMAP8BITATTRIBUTE_IMPL_H_
#define ZCLBITMAP8BITATTRIBUTE_IMPL_H_

#include <ostream>
#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "zcl/attributeTypes/ZCLbitmap8bitAttribute.h"

namespace zigbee {

    class ZCLBitmap8bitAttributeImpl : public ZCLBitmap8bitAttribute, public ZCLAttributeImpl {
    public:
        ZCLBitmap8bitAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                   std::string_view name, bool readOnly) :
                ZCLAttributeImpl(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLType8bitBitmap, name, readOnly) {
        };

    public:
        std::any getValue() const override;

        void setValue(std::any &value) override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }


        void setRawValue(uint8_t *rawData) override;

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

        friend std::ostream &operator<<(std::ostream &out, const ZCLBitmap8bitAttributeImpl *);

    private:
        ZclAttributeRawValueImpl<type> zclAttributeRawValueImpl;
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCLBitmap8bitAttribute *);


} /* namespace zigbee */

#endif /* ZCLBITMAP8BITATTRIBUTE_H_ */
