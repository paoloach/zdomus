/*
 * RelativeHumidityMeasuramentCluster.h
 *
 *  Created on: 11/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_

#include <string>
#include "src/zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class RelativeHumidityMeasurementCluster : public ClusterImpl{
public:
	RelativeHumidityMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_RELATIVEHUMIDITYMEASURAMENTCLUSTER_H_ */
