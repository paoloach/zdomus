/*
 * FlowMeasurementCluster.h
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_FLOWMEASUREMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_FLOWMEASUREMENTCLUSTER_H_

#include <string>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class FlowMeasurementCluster : public Cluster{
public:
	FlowMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_FLOWMEASUREMENTCLUSTER_H_ */
