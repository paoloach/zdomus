//
// Created by Paolo Achdjian on 11/19/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCL_uint32_Attribute: public ZCLAttribute {
	union Converter {
		uint32_t value;
		uint8_t raw[4];
	};
public:
	ZCL_uint32_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
	virtual ~ZCL_uint32_Attribute(){};
public:
	virtual  boost::any getValue() const override;
	virtual void sendValue(uint32_t newValue);
	static ZCLTypeDataType type(){
		return ZCLTypeDataType::ZCLTypeUInt32;
	}
	static std::string name() {
		return "UInt32";
	}
private:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);
	friend std::ostream & operator<<(std::ostream & out, const ZCL_uint32_Attribute *);
private:
	uint32_t value;
};

std::ostream & operator<<(std::ostream & out, const ZCL_uint32_Attribute *);

} /* namespace zigbee */

#endif //ZIGBEE_LIB_ZCLUINT32ATTRIBUTE_H
