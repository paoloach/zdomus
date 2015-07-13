/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "ZCLuint8Attribute.h"
#include "../StatusEnum.h"
#include "../ZCLDataType.h"
#include "../Cluster.h"

namespace zigbee {

ZCL_uint8_Attribute::ZCL_uint8_Attribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly) :
		ZCLAttribute(zigbeeDevice, parent, identifier,ZCLTypeDataType::ZCLTypeUInt8, name,readOnly) {
	if (zigbeeDevice){
		zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(), identifier, boost::bind(&ZCL_uint8_Attribute::setValue, this, _1));
	}
}

ZCL_uint8_Attribute::~ZCL_uint8_Attribute() {
}

boost::any ZCL_uint8_Attribute::getValue() const {
	if (status != Available) {
		throw ZCLAttributeNotAvailableException(parent, identifier);
	}
	return boost::any(value);
}

void ZCL_uint8_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData) {
	value = *rawData->data;
}

void ZCL_uint8_Attribute::sendValue(uint8_t newValue) {
	sendValueToDevice(1, &newValue);
}

std::ostream & operator<<(std::ostream & out, const ZCL_uint8_Attribute * attribute) {
	out << attribute->value;
	return out;
}

} /* namespace zigbee */
