/*
 * OnOffCluster.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include "OnOffCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeBool, 0, "On/Off", true),
		};

On_Off_Cluster::On_Off_Cluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress){

	createAttributes(attributesDef);

	_commandsDef.emplace_back([=](std::vector<uint8_t> && ) { zigbeeDevice->sendCmd(networkAddress,  endpoint, OnOffClusterID, 0);}, 0, "Off");
	_commandsDef.emplace_back([=](std::vector<uint8_t> && ) { zigbeeDevice->sendCmd(networkAddress,  endpoint, OnOffClusterID, 1);}, 1, "On");
	_commandsDef.emplace_back([=](std::vector<uint8_t> && ) { zigbeeDevice->sendCmd(networkAddress,  endpoint, OnOffClusterID, 2);}, 2, "Toggle");
}

ClusterID On_Off_Cluster::getId() const  {
	return OnOffClusterID;
}

std::string On_Off_Cluster::getClusterName()  const {
	return "On/Off";
}

} /* namespace zigbee */
