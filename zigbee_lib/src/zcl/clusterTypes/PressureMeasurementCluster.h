/*
 * PressureMeasurementCluster.h
 *
 *  Created on: 10/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_PRESSUREMEASUREMENTCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_PRESSUREMEASUREMENTCLUSTER_H_

#include <string>
#include <memory>
#include "src/zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class PressureMeasurementCluster : public ClusterImpl{
public:
	PressureMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_PRESSUREMEASUREMENTCLUSTER_H_ */
