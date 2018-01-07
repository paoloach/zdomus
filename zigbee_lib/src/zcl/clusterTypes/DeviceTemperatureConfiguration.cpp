/*
 * DeviceTemperatureConfiguration.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include "DeviceTemperatureConfiguration.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0, "Current Temperature",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 1, "Min Temp Experienced",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 2, "Max Temp. Experienced", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 3, "Over Temp. Total Dwell, true"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x10, "Allarm Mask"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x11, "Low Temperature Threshold"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x12, "High Temperature Threshold"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x13, "Low Temp. Dwell Trip Point"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x14, "High Temp. Dwell Trip Point")
};

DeviceTemperatureConfiguration::DeviceTemperatureConfiguration(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID DeviceTemperatureConfiguration::getId() const {
	return DeviceTemperatureConfigClusterID;
}

std::string DeviceTemperatureConfiguration::getClusterName() const  {
	return "Device Temperature Configuration";
}

} /* namespace zigbee */
