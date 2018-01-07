/*
 * OccupancySensingCluster.cpp
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#include "OccupancySensingCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0, "Occupancy", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 1, "Occupancy Sensor Type", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x10, "PIR Occupied to Unoccupied Delay"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x11, "PIR Unoccupied to Occupied Delay"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x12, "PIR Unoccupied to Occupied Threshold"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x20, "Ultrasonic Occupied to Unoccupied Delay"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x21, "Ultrasonic Unoccupied to Occupied Delay"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x22, "Ultrasonic Unoccupied to Occupied Threshold")
};

OccupancySensingCluster::OccupancySensingCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID OccupancySensingCluster::getId()  const {
	return OccupancySensingID;
}

std::string OccupancySensingCluster::getClusterName() const  {
	return "Occupancy Sensing";
}

} /* namespace zigbee */
