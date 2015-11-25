/*
 * NullCluster.cpp
 *
 *  Created on: 30/lug/2014
 *      Author: Paolo Achdjian
 */

#include "NullCluster.h"

namespace zigbee {

NullCluster::NullCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress, ClusterID clusterId):
	Cluster(zigbeeDevice, endpoint, networkAddress), clusterId(clusterId){
}

ClusterID NullCluster::getId()  const {
	return clusterId;
}

std::string NullCluster::getClusterName() const  {
	return "Invalid cluster";
}

} /* namespace zigbee */
