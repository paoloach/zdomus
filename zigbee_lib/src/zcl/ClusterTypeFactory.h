/*
 * ClusterTypeFactory.h
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef CLUSTERTYPEFACTORY_H_
#define CLUSTERTYPEFACTORY_H_

#include <memory>
#include "../zigbee/ZigbeeDevice.h"
#include "Cluster.h"
#include "ClustersEnum.h"
#include "clusterTypes/BasicCluster.h"
#include "../zigbee/EndpointID.h"

namespace zigbee {

class ClusterTypeFactory {
public:
	static std::shared_ptr<Cluster> createCluster(ClusterID clusterId, ZigbeeDevice * zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
	virtual ~ClusterTypeFactory() = default;
	virtual std::shared_ptr<Cluster> getCluster(ClusterID clusterId,  ZigbeeDevice * zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
};

} /* namespace zigbee */

#endif /* CLUSTERTYPEFACTORY_H_ */
