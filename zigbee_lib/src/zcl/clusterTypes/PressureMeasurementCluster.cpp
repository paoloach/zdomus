/*
 * PressureMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "PressureMeasurementCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x10, "Scaled Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x11, "Min Scaled Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x12, "Max Scaled Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x13, "Scaled Tollerance", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x14, "Scale", true)
		};

PressureMeasurementCluster::PressureMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
								ClusterImpl(zigbeeDevice, endpoint, networkAddress) {

	createAttributes(attributesDef);
}

ClusterID PressureMeasurementCluster::getId()  const {
	return PressureMeasurementID;
}

std::string PressureMeasurementCluster::getClusterName()  const {
	return "Pressure Measurement";
}

} /* namespace zigbee */
