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

class ZCL_boolean_Attribute : public ZCLAttribute {
public:
	ZCL_boolean_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
	virtual ~ZCL_boolean_Attribute();
public:
	virtual boost::any getValue() const override;
	virtual void sendValue(bool value);
    static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeBool;
	static std::string name() {
		return "Boolean";
	}
private:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData);
	friend std::ostream & operator<<(std::ostream & out, const ZCL_boolean_Attribute *);
private:
	bool value;
};

std::ostream & operator<<(std::ostream & out, const ZCL_boolean_Attribute *);

} /* namespace zigbee */

#endif /* ZCLBOOLEANATTRIBUTE_H_ */
