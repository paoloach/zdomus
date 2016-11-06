/*
 * PowerConfigurationCluster.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include "../attributeTypes/ZCLuint8Attribute.h"
#include "PowerConfigurationCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef = {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Mains Voltage",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 1, "Mains Frequency",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x10, "Mains Alarm Mask"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x12, "Mains Voltage Min Threshold"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x13, "Mains Voltage Max Threshold"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x14, "Mains Voltage Dwell TripPoint"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x20, "Battery Voltage",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 0x30, "Battery Manufacturer"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x31, "Battery Size"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x32, "Battery AHrRating"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x33, "Battery Quantity"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x34, "Battery Rated Voltage"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x35, "Battery Alarm Mask"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x36, "Battery Voltage Min Threshold")
};

PowerConfigurationCluster::PowerConfigurationCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);

}

ClusterID PowerConfigurationCluster::getId()  const {
	return PowerConfigurationClusterID;
}

std::string PowerConfigurationCluster::getClusterName()  const {
	return "Power configuration";
}

} /* namespace zigbee */
