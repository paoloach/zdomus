/*
 * PowerConfigurationCluster.h
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef POWERCONFIGURATIONCLUSTER_H_
#define POWERCONFIGURATIONCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class PowerConfigurationCluster : public Cluster{
public:
	PowerConfigurationCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* POWERCONFIGURATIONCLUSTER_H_ */
