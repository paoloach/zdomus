/*
 * ZCLbooleanAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLbooleanAttribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_boolean_Attribute::ZCL_boolean_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeBool, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
				boost::bind(&ZCL_boolean_Attribute::setValue, this, _1));
	}

}

ZCL_boolean_Attribute::~ZCL_boolean_Attribute() {
}

boost::any ZCL_boolean_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any (value);
}

void ZCL_boolean_Attribute::sendValue(bool newValue) {
	sendValueToDevice(1, (uint8_t *) &newValue);
}

void ZCL_boolean_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	value = *rawData->data;
}

std::ostream & operator<<(std::ostream & out, const ZCL_boolean_Attribute * attribute) {
	out << attribute->value ? "true" : "false";
	return out;
}

} /* namespace zigbee */
