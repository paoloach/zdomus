/*
 * PressureMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "PressureMeasurementCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x10, "Scaled Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x11, "Min Scaled Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x12, "Max Scaled Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x13, "Scaled Tollerance", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x14, "Scale", true)
		};

PressureMeasurementCluster::PressureMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
								Cluster(zigbeeDevice, endpoint, networkAddress) {

	createAttributes(attributesDef);
}

ClusterID PressureMeasurementCluster::getId() {
	return PressureMeasurementID;
}

std::string PressureMeasurementCluster::getClusterName() {
	return "Pressure Measurement";
}

} /* namespace zigbee */
