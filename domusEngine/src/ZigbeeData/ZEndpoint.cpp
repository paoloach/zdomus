/*
 * ZEndpoint.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include <algorithm>
#include <iostream>
#include "ZEndpoint.h"

namespace zigbee {


ZEndpoint::ZEndpoint(const SimpleDescMessage & simpleDescMessage) : nwkAddr{simpleDescMessage.nwkAddr},endpoint{simpleDescMessage.endpoint}{
	appProfId = simpleDescMessage.appProfId;
	appDeviceId = simpleDescMessage.appDeviceId;
	appDevVer = simpleDescMessage.appDevVer;

	const uint16_t * clustersList = simpleDescMessage.clustersList;
	for (int i = 0; i < simpleDescMessage.numInClusters; i++) {
		inCluster.emplace_back(*clustersList);
		clustersList++;
	}
	for (int i = 0; i < simpleDescMessage.numOutClusters; i++) {
		outCluster.emplace_back(*clustersList);
		clustersList++;
	}
}

bool ZEndpoint::operator==(const ZEndpoint & other) {
	return nwkAddr == other.nwkAddr && endpoint == other.endpoint && appProfId == other.appProfId && appDeviceId == other.appDeviceId && appDevVer == other.appDevVer
			&& inCluster == other.inCluster && outCluster == other.outCluster;
}

bool ZEndpoint::hasInCluster(ClusterID clusterId) const noexcept {
	return std::find(inCluster.begin(), inCluster.end(),clusterId) != inCluster.end();
}

bool ZEndpoint::isInCluster(ClusterID clusterId) const noexcept{
	return std::find(inCluster.begin(), inCluster.end(), clusterId) != inCluster.end();
}

bool ZEndpoint::isOutCluster(ClusterID clusterId) const noexcept{
	return std::find(outCluster.begin(), outCluster.end(), clusterId) != outCluster.end();
}

} /* namespace zigbee */

