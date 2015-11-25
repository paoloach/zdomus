/*
 * LevelControlCluster.h
 *
 *  Created on: 07/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_LEVELCONTROLCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_LEVELCONTROLCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class LevelControlCluster : public Cluster{
public:
	LevelControlCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId() const override;
	virtual std::string getClusterName() const override;
protected:
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_LEVELCONTROLCLUSTER_H_ */
