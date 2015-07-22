/*
 * GroupsCluster.h
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef GROUPSCLUSTER_H_
#define GROUPSCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class GroupsCluster  : public Cluster{
public: // Commands Params Types

public:
	GroupsCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId();
	virtual std::string getClusterName();
protected:
};

} /* namespace zigbee */

#endif /* GROUPSCLUSTER_H_ */