/*
 * TemperatureMeasurementCluster.h
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_TEMPERATUREMEASUREMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_TEMPERATUREMEASUREMENTCLUSTER_H_

#include <string>
#include <memory>
#include "src/zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class TemperatureMeasurementCluster : public ClusterImpl{
public:
	TemperatureMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_TEMPERATUREMEASUREMENTCLUSTER_H_ */
