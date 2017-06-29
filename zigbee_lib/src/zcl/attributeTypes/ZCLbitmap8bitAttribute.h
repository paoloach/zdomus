/*
 * ZCLbitmap8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBITMAP8BITATTRIBUTE_H_
#define ZCLBITMAP8BITATTRIBUTE_H_

#include <ostream>
#include "../../zigbee/ResponseCallback.h"
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

    class ZCL_bitmap8bit_Attribute : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLType8bitBitmap> {
    public:
        ZCL_bitmap8bit_Attribute(ZigbeeDevice *zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                 std::experimental::string_view name, bool readOnly);

    public:
        boost::any getValue() const override;

        std::string getStrValue() const override {
            return std::to_string(value);
        }

        virtual void sendValue(uint8_t newValue);

        virtual bool getValue(int bitIndex) const;

        static std::string name() {
            return "8bitBitmap";
        }

    private:
        void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) override;

        void internalSetValue(uint8_t *rawData) override;

        friend std::ostream &operator<<(std::ostream &out, const ZCL_bitmap8bit_Attribute *);

    private:
        uint32_t value;
    };

    std::ostream &operator<<(std::ostream &out, const ZCL_bitmap8bit_Attribute *);


} /* namespace zigbee */

#endif /* ZCLBITMAP8BITATTRIBUTE_H_ */
