/*
 * DeviceTemperatureConfiguration.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include "DeviceTemperatureConfiguration.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0, "Current Temperature",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 1, "Min Temp Experienced",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 2, "Max Temp. Experienced", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 3, "Over Temp. Total Dwell, true"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x10, "Allarm Mask"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x11, "Low Temperature Threshold"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x12, "High Temperature Threshold"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x13, "Low Temp. Dwell Trip Point"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x14, "High Temp. Dwell Trip Point")
};

DeviceTemperatureConfiguration::DeviceTemperatureConfiguration(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID DeviceTemperatureConfiguration::getId() const {
	return DeviceTemperatureConfigClusterID;
}

std::string DeviceTemperatureConfiguration::getClusterName() const  {
	return "Device Temperature Configuration";
}

} /* namespace zigbee */
