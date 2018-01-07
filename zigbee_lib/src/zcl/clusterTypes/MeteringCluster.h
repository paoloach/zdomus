/*
 * MeteringCluster.h
 *
 *  Created on: 07/ago/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_
#define SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_

#include <string>
#include <memory>
#include "src/zcl/impl/ClusterImpl.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class MeteringCluster : public ClusterImpl {
public:
	MeteringCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* SRC_ZCL_CLUSTERTYPES_METERINGCLUSTER_H_ */
