/*
 * FlowMeasurementCluster.cpp
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#include <vector>
#include "FlowMeasurementCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true)
};

FlowMeasurementCluster::FlowMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
										ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);
}

ClusterID FlowMeasurementCluster::getId() const  {
	return FlowMeasurementID;
}

std::string FlowMeasurementCluster::getClusterName()  const {
	return "Flow Measurement";
}

} /* namespace zigbee */
