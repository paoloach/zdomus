/*
 * TemperatureMeasurementCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "TemperatureMeasurementCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef = {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0, "Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 1, "Min Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 2, "Max Measured Value", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 3, "Tollerance", true)
		};

TemperatureMeasurementCluster::TemperatureMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
						Cluster(zigbeeDevice, endpoint, networkAddress){

	createAttributes(attributesDef);

}

ClusterID TemperatureMeasurementCluster::getId() const{
	return TemperatureMeasurementID;
}

std::string TemperatureMeasurementCluster::getClusterName()  const{
	return "Temperature Measurement";
}

} /* namespace zigbee */
