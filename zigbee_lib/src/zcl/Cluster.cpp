/*
 * Cluster.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <exception>
#include <iostream>
#include <algorithm>
#include "Cluster.h"
#include "attributeTypes/ZCLuint8Attribute.h"
#include "attributeTypes/ZCLuint16Attribute.h"
#include "attributeTypes/ZCLuint24Attribute.h"
#include "attributeTypes/ZCLint16Attribute.h"
#include "attributeTypes/ZCLstringAttribute.h"
#include "attributeTypes/ZCLbitmap8bitAttribute.h"
#include "attributeTypes/ZCLbooleanAttribute.h"
#include "attributeTypes/ZCLenum8bitAttribute.h"
#include "attributeTypes/ZCLIEEEAddressAttribute.h"
#include "exceptions/AttributeNotFoundException.h"

using std::copy;
using std::back_inserter;

namespace zigbee {

Cluster::Cluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		zigbeeDevice(zigbeeDevice), endpoint(endpoint), networkAddress(networkAddress) {

}

void Cluster::createAttributes(const std::vector<Cluster::AttributeDef> & attributesDef) {
	attributes.clear();
	copy(attributesDef.begin(), attributesDef.end(), back_inserter(_attributesDef));
	for (const Cluster::AttributeDef & attributeDef : attributesDef) {
		attributes.push_back(createAttribute(attributeDef));
	}
}

void Cluster::executeComand(uint32_t cmdId,  std::vector<uint8_t> data) {
	auto found = std::find_if(_commandsDef.begin(), _commandsDef.end(), [cmdId](const CommandDef & cmd)->bool {return cmd.cmdId == cmdId;});
	if (found != _commandsDef.end()) {
		(*found).cmd(std::move(data));
	}
}

std::shared_ptr<ZCLAttribute> Cluster::createAttribute(const AttributeDef & attributeDef) {
	switch (attributeDef.type) {
		case ZCLTypeDataType::ZCLTypeenum8:
			return createAttribute<ZCL_enum8bit_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeSInt16:
			return createAttribute<ZCL_int16_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeUInt8:
			return createAttribute<ZCL_uint8_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeUInt16:
			return createAttribute<ZCL_uint16_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeUInt24:
			return createAttribute<ZCL_uint24_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLType8bitBitmap:
			return createAttribute<ZCL_bitmap8bit_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeStringChar:
			return createAttribute<ZCL_string_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeBool:
			return createAttribute<ZCL_boolean_Attribute>(attributeDef);
		case ZCLTypeDataType::ZCLTypeIEEEaddress:
			return createAttribute<ZCLIEEEAddressAttribute>(attributeDef);
		default:
			std::cerr << __FILE__ << ":" << __LINE__ << ": Used an invalid type: " << attributeDef.type << std::endl;
			throw std::exception();
	}
}

std::shared_ptr<ZCLAttribute> Cluster::getAttribute(int id) const {
	for (auto & attribute : attributes) {
		if (attribute->getIdentifier() == id) {
			return attribute;
		}
	}
	return std::shared_ptr<ZCLAttribute>();
}

std::shared_ptr<ZCLAttribute> Cluster::getAttribute(const std::string& name) const {
	for (auto & attribute : attributes) {
		if (attribute->getName() == name) {
			return attribute;
		}
	}
	throw AttributeNotFoundException();
}

std::vector<std::shared_ptr<ClusterCmdParamsBase> > Cluster::getCmdParams(uint32_t cmdId) {
	auto found = std::find_if(_commandsDef.begin(), _commandsDef.end(), [cmdId](const CommandDef & cmd)->bool {return cmd.cmdId == cmdId;});
	if (found != _commandsDef.end()) {
		return found->params;
	}
	return std::vector<std::shared_ptr<ClusterCmdParamsBase> > { };
}

void Cluster::printRawData(const std::vector<uint8_t>& data) {
	for (uint8_t d : data) {
		std::cout << (int) (d) << " ";
	}
	std::cout << std::endl;
}

} /* namespace zigbee */

