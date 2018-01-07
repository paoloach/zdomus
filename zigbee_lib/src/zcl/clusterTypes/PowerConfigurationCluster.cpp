/*
 * PowerConfigurationCluster.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include "src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.h"
#include "PowerConfigurationCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Mains Voltage",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 1, "Mains Frequency",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x10, "Mains Alarm Mask"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x12, "Mains Voltage Min Threshold"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x13, "Mains Voltage Max Threshold"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x14, "Mains Voltage Dwell TripPoint"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x20, "Battery Voltage",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 0x30, "Battery Manufacturer"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x31, "Battery Size"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x32, "Battery AHrRating"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x33, "Battery Quantity"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x34, "Battery Rated Voltage"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x35, "Battery Alarm Mask"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x36, "Battery Voltage Min Threshold")
};

PowerConfigurationCluster::PowerConfigurationCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);

}

ClusterID PowerConfigurationCluster::getId()  const {
	return PowerConfigurationClusterID;
}

std::string PowerConfigurationCluster::getClusterName()  const {
	return "Power configuration";
}

} /* namespace zigbee */
