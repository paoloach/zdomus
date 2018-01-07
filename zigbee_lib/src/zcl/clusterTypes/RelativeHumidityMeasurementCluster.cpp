/*
 * RelativeHumidityMeasurementCluster.cpp
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#include "RelativeHumidityMeasurementCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1, "Min Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Max Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true)
};

RelativeHumidityMeasurementCluster::RelativeHumidityMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
												ClusterImpl(zigbeeDevice, endpoint, networkAddress){
	createAttributes(attributesDef);
}

ClusterID RelativeHumidityMeasurementCluster::getId()  const {
	return RelativeHumidityMeasurementID;
}

std::string RelativeHumidityMeasurementCluster::getClusterName()  const {
	return "Relative Humidity Measurement";
}

} /* namespace zigbee */
