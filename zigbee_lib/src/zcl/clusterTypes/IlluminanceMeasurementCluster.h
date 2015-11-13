/*
 * IlluminanceMeasurementCluster.h
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_ILLUMINANCEMEASUREMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_ILLUMINANCEMEASUREMENTCLUSTER_H_

#include <string>
#include <memory>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class IlluminanceMeasurementCluster : public Cluster{
public:
	IlluminanceMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId();
	virtual std::string getClusterName();
protected:
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_ILLUMINANCEMEASUREMENTCLUSTER_H_ */
