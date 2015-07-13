/*
 * OccupancySensingCluster.cpp
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#include "OccupancySensingCluster.h"

#include <vector>
namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef = {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0, "Occupancy", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 1, "Occupancy Sensor Type", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x10, "PIR Occupied to Unoccupied Delay"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x11, "PIR Unoccupied to Occupied Delay"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x12, "PIR Unoccupied to Occupied Threshold"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x20, "Ultrasonic Occupied to Unoccupied Delay"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x21, "Ultrasonic Unoccupied to Occupied Delay"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x22, "Ultrasonic Unoccupied to Occupied Threshold")
};

OccupancySensingCluster::OccupancySensingCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID OccupancySensingCluster::getId() {
	return OccupancySensingID;
}

std::string OccupancySensingCluster::getClusterName() {
	return "Occupancy Sensing";
}

} /* namespace zigbee */
