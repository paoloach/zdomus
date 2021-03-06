/*
 * OnOffCluster.h
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ONOFFCLUSTER_H_
#define ONOFFCLUSTER_H_

#include <string>
#include <memory>
#include "zcl/impl/ClusterImpl.h"
#include "zigbee/ZigbeeDevice.h"

namespace zigbee {

class On_Off_Cluster: public ClusterImpl{
public:
	On_Off_Cluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
protected:
};

} /* namespace zigbee */

#endif /* ONOFFCLUSTER_H_ */
