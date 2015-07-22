/*
 * FlowMeasurementCluster.cpp
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#include <vector>
#include "FlowMeasurementCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef = {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true)
};

FlowMeasurementCluster::FlowMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
										Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID FlowMeasurementCluster::getId() {
	return FlowMeasurementID;
}

std::string FlowMeasurementCluster::getClusterName() {
	return "Flow Measurement";
}

} /* namespace zigbee */