/*
 * NullCluster.h
 *
 *  Created on: 30/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef NULLCLUSTER_H_
#define NULLCLUSTER_H_

#include "src/zcl/impl/ClusterImpl.h"

namespace zigbee {

class NullCluster : public ClusterImpl {
public:
	NullCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress,ClusterID clusterId);
public:
	ClusterID getId() const override;
	std::string getClusterName() const override;
private:
	ClusterID clusterId;
};

} /* namespace zigbee */

#endif /* NULLCLUSTER_H_ */
