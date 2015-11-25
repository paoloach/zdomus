/*
 * NullCluster.h
 *
 *  Created on: 30/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef NULLCLUSTER_H_
#define NULLCLUSTER_H_

#include "../Cluster.h"

namespace zigbee {

class NullCluster : public Cluster {
public:
	NullCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress,ClusterID clusterId);
public:
	virtual ClusterID getId() const override;
	virtual std::string getClusterName() const override;
private:
	ClusterID clusterId;
};

} /* namespace zigbee */

#endif /* NULLCLUSTER_H_ */
