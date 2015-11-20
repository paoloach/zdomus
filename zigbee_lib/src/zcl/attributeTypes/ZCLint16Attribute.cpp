/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLint16Attribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_int16_Attribute::ZCL_int16_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeSInt16, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
				boost::bind(&ZCL_int16_Attribute::setValue, this, _1));
	}
}

boost::any ZCL_int16_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value);
}

void ZCL_int16_Attribute::sendValue(int16_t newValue) {
	sendValueToDevice(2, (uint8_t *) &newValue);
}

void ZCL_int16_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	Converter converter;
	converter.raw[0] = *rawData->data;
	converter.raw[1] = *(rawData->data + 1);
	value = converter.value;
}

std::ostream & operator<<(std::ostream & out, const ZCL_int16_Attribute * attribute) {
	out << attribute->value;
	return out;
}

} /* namespace zigbee */
