/*
 * ScenesCluster.h
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef SCENESCLUSTER_H_
#define SCENESCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class ScenesCluster: public Cluster{
public:
	ScenesCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId();
	virtual std::string getClusterName();
protected:
};

} /* namespace zigbee */

#endif /* SCENESCLUSTER_H_ */
