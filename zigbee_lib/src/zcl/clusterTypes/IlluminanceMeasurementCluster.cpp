/*
 * IlluminanceMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "IlluminanceMeasurementCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 4, "Light Sensor Type", true)
		};

IlluminanceMeasurementCluster::IlluminanceMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
				Cluster(zigbeeDevice, endpoint, networkAddress){
	createAttributes(attributesDef);
}

ClusterID IlluminanceMeasurementCluster::getId() {
	return IlluminanceMeasureID;
}

std::string IlluminanceMeasurementCluster::getClusterName() {
	return "Illuminance measurement";
}

} /* namespace zigbee */
