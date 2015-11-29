/*
 * ZCLIEEEAddressAttribute.cpp
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#include <ios>

#include "ZCLIEEEAddressAttribute.h"
#include "../Cluster.h"

namespace zigbee {

ZCLIEEEAddressAttribute::ZCLIEEEAddressAttribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeIEEEaddress, name, readOnly) {
	if (zigbeeDevice) {
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier,
												[this](std::shared_ptr<AttributeStatusRecord> rawData){setValue(rawData);});
	}

}

ZCLIEEEAddressAttribute::~ZCLIEEEAddressAttribute() {
}

boost::any ZCLIEEEAddressAttribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value.data);
}

void ZCLIEEEAddressAttribute::sendValue(uint64_t newValue) {
	sendValueToDevice(8, (uint8_t *) &newValue);
}

void ZCLIEEEAddressAttribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
	value.raw[0] = rawData->data[0];
	value.raw[1] = rawData->data[1];
	value.raw[2] = rawData->data[2];
	value.raw[3] = rawData->data[3];
	value.raw[4] = rawData->data[4];
	value.raw[5] = rawData->data[5];
	value.raw[6] = rawData->data[6];
	value.raw[7] = rawData->data[7];
}

const uint8_t * ZCLIEEEAddressAttribute::getRawValue() const {
	return value.raw;
}

std::ostream & operator<<(std::ostream & out, const ZCLIEEEAddressAttribute * attribute) {
	const uint8_t * ieeeAddress = attribute->getRawValue();
	out.fill('0');
	out.width(2);
	for (int i = 7; i > 0; i--) {
		out << std::hex << ieeeAddress[i] << " - ";
	}
	out << std::hex << ieeeAddress[0];
	return out;
}

} /* namespace zigbee */
