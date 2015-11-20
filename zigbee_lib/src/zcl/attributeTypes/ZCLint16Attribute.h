/*
 * ZCLuint16Attribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLint16ATTRIBUTE_H_
#define ZCLint16ATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCL_int16_Attribute : public ZCLAttribute {
private:
	union Converter {
		int16_t value;
		uint8_t raw[2];
	};
public:
	ZCL_int16_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
public:
	virtual  boost::any getValue() const override;
	virtual  void sendValue(int16_t newValue);
	static ZCLTypeDataType type(){
		return ZCLTypeDataType::ZCLTypeSInt16;
	}
	static std::string name() {
		return "Int16";
	}
private:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData);
	friend std::ostream & operator<<(std::ostream & out, const ZCL_int16_Attribute *);
private:
	int32_t value;
};

std::ostream & operator<<(std::ostream & out, const ZCL_int16_Attribute *);


} /* namespace zigbee */

#endif /* ZCLint16ATTRIBUTE_H_ */
