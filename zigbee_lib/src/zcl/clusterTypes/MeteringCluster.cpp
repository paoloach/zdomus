/*
 * MeteringCluster.cpp
 *
 *  Created on: 07/ago/2015
 *      Author: Paolo Achdjian
 */

#include "../attributeTypes/ZCLuint8Attribute.h"
#include "MeteringCluster.h"

namespace zigbee {

MeteringCluster::MeteringCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {

}

ClusterID MeteringCluster::getId() {
	return Metering;
}

std::string MeteringCluster::getClusterName() {
	return "Metering";
}

} /* namespace zigbee */
