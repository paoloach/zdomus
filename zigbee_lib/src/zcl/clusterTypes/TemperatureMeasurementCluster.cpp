/*
 * TemperatureMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "TemperatureMeasurementCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0, "Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 1, "Min Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 2, "Max Measured Value", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true)
		};

TemperatureMeasurementCluster::TemperatureMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
						ClusterImpl(zigbeeDevice, endpoint, networkAddress){

	createAttributes(attributesDef);

}

ClusterID TemperatureMeasurementCluster::getId() const{
	return TemperatureMeasurementID;
}

std::string TemperatureMeasurementCluster::getClusterName()  const{
	return "Temperature Measurement";
}

} /* namespace zigbee */
