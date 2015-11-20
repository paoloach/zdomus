/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint16Attribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_uint16_Attribute::ZCL_uint16_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt16, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
				boost::bind(&ZCL_uint16_Attribute::setValue, this, _1));
	}
}

boost::any ZCL_uint16_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value);
}

void ZCL_uint16_Attribute::sendValue(uint16_t newValue) {
	sendValueToDevice(2, (uint8_t *) &newValue);
}

void ZCL_uint16_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	value =(uint32_t) (*rawData->data) + 256 * (*(rawData->data + 1));
}

std::ostream & operator<<(std::ostream & out, const ZCL_uint16_Attribute * attribute) {
	out << attribute->value;
	return out;
}

} /* namespace zigbee */
