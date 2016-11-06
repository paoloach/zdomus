/*
 * IlluminanceLevelSensingCluster.cpp
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#include "IlluminanceLevelSensingCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0, "Level Status", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 1, "Level Sensor Type", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0x10, "Illuminance Target Level", true)
		};

IlluminanceLevelSensingCluster::IlluminanceLevelSensingCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
				Cluster(zigbeeDevice, endpoint, networkAddress){

	createAttributes(attributesDef);
}

ClusterID IlluminanceLevelSensingCluster::getId()  const {
	return IlluminanceLevelSensingID;
}

std::string IlluminanceLevelSensingCluster::getClusterName()  const {
	return "Illuminance Level Sensing";
}

} /* namespace zigbee */
