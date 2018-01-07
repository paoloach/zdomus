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
#include "src/zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class ScenesCluster: public ClusterImpl{
public:
	ScenesCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
protected:
};

} /* namespace zigbee */

#endif /* SCENESCLUSTER_H_ */
