/*
 * ZCLenum8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLENUM8BITATTRIBUTE_H_
#define ZCLENUM8BITATTRIBUTE_H_

#include "ZCLuint8Attribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCL_enum8bit_Attribute: public ZCL_uint8_Attribute {
public:
	ZCL_enum8bit_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
	virtual ~ZCL_enum8bit_Attribute();
public:
	virtual void sendValue(uint8_t newValue);
    static const ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeenum8;
	static std::string name() {
		return "8BitEnum";
	}
	friend std::ostream & operator<<(std::ostream & out, const ZCL_enum8bit_Attribute *);
private:
};

std::ostream & operator<<(std::ostream & out, const ZCL_enum8bit_Attribute *);

} /* namespace zigbee */

#endif /* ZCLENUM8BITATTRIBUTE_H_ */
