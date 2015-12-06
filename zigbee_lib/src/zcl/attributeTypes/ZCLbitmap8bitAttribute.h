/*
 * ZCLbitmap8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBITMAP8BITATTRIBUTE_H_
#define ZCLBITMAP8BITATTRIBUTE_H_

#include <ostream>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCL_bitmap8bit_Attribute : public ZCLAttribute {
public:
	ZCL_bitmap8bit_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
public:
	virtual boost::any getValue() const override;
	virtual void sendValue(uint8_t newValue);
	virtual bool getValue(int bitIndex) const;

	static std::string name() {
		return "8bitBitmap";
	}

    static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLType8bitBitmap;
private:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData);
	friend std::ostream & operator<<(std::ostream & out, const ZCL_bitmap8bit_Attribute *);
private:
	uint32_t value;
};

std::ostream & operator<<(std::ostream & out, const ZCL_bitmap8bit_Attribute *);



} /* namespace zigbee */

#endif /* ZCLBITMAP8BITATTRIBUTE_H_ */
