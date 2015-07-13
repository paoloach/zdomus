/*
 * OccupancySensingCluster.h
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_OCCUPANCYSENSINGCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_OCCUPANCYSENSINGCLUSTER_H_

#include <string>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class OccupancySensingCluster : public Cluster{
public:
	OccupancySensingCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId();
	virtual std::string getClusterName();
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_OCCUPANCYSENSINGCLUSTER_H_ */
