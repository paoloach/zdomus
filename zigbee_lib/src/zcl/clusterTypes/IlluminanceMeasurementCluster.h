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
#include "zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class IlluminanceMeasurementCluster : public ClusterImpl{
public:
	IlluminanceMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
private:
	ClusterID getId() const override;
	std::string getClusterName() const override;
protected:
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_ILLUMINANCEMEASUREMENTCLUSTER_H_ */
