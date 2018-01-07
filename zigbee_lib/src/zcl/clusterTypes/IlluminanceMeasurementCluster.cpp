/*
 * IlluminanceMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "IlluminanceMeasurementCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 4, "Light Sensor Type", true)
		};

IlluminanceMeasurementCluster::IlluminanceMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
				ClusterImpl(zigbeeDevice, endpoint, networkAddress){
	createAttributes(attributesDef);
}

ClusterID IlluminanceMeasurementCluster::getId()  const {
	return IlluminanceMeasureID;
}

std::string IlluminanceMeasurementCluster::getClusterName()  const {
	return "Illuminance measurement";
}

} /* namespace zigbee */
