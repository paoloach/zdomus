/*
 * NullCluster.cpp
 *
 *  Created on: 30/lug/2014
 *      Author: Paolo Achdjian
 */

#include "NullCluster.h"
#include "../ClustersEnum.h"

namespace zigbee {

NullCluster::NullCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress, ClusterID clusterId):
	Cluster(zigbeeDevice, endpoint, networkAddress), clusterId(clusterId){
}

ClusterID NullCluster::getId() {
	return clusterId;
}

std::string NullCluster::getClusterName() {
	return "Invalid cluster";
}

} /* namespace zigbee */
