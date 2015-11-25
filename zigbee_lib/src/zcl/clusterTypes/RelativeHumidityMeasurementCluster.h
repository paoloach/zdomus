/*
 * RelativeHumidityMeasuramentCluster.h
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_

#include <string>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class RelativeHumidityMeasurementCluster : public Cluster{
public:
	RelativeHumidityMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	virtual ClusterID getId() const override;
	virtual std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_ */
