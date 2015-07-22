/*
 * ZCLstringAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLstringAttribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_string_Attribute::ZCL_string_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeStringChar, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
				boost::bind(&ZCL_string_Attribute::setValue, this, _1));
	}
}

ZCL_string_Attribute::~ZCL_string_Attribute() {
}

boost::any ZCL_string_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value);
}

void ZCL_string_Attribute::sendValue(const std::string & newValue) {
	uint8_t data[1 + value.length()];
	data[0] = value.length();
	memcpy(data + 1, value.c_str(), value.length());
	sendValueToDevice(1 + value.length(), data);
}

void ZCL_string_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	uint8_t len = *(rawData->data);
	value = std::string();
	value.resize(len);
	for (int i = 0; i < len; i++) {
		value[i] = rawData->data[i + 1];
	}
}

std::ostream & operator<<(std::ostream & out, const ZCL_string_Attribute * attribute) {
	out << attribute->value;
	return out;
}

} /* namespace zigbee */