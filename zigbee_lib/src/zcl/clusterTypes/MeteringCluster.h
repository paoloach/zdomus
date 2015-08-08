/*
 * MeteringCluster.h
 *
 *  Created on: 07/ago/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class MeteringCluster : public Cluster {
public:
	MeteringCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
	virtual ClusterID getId();
	virtual std::string getClusterName();
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_ */
