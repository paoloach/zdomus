/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLuint24Attribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_uint24_Attribute::ZCL_uint24_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier,std::experimental::string_view name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUInt24, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
												[this](std::shared_ptr<AttributeStatusRecord> rawData){setValue(rawData);});
	}
}

boost::any ZCL_uint24_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value);
}

void ZCL_uint24_Attribute::sendValue(uint32_t newValue) {
	sendValueToDevice(3, (uint8_t *) &newValue);
}

void ZCL_uint24_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	Converter converter;
	converter.raw[0] = *rawData->data;
	converter.raw[1] = *(rawData->data + 1);
	converter.raw[2] = *(rawData->data + 2);
	converter.raw[3] = 0;
	value = converter.value;
}

std::ostream & operator<<(std::ostream & out, const ZCL_uint24_Attribute * attribute) {
	out << attribute->value;
	return out;
}

} /* namespace zigbee */
