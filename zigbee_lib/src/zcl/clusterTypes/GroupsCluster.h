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
#include "zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class GroupsCluster  : public ClusterImpl{
public: // Commands Params Types

public:
	GroupsCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
protected:
};

} /* namespace zigbee */

#endif /* GROUPSCLUSTER_H_ */
