/*
 * IdentifyCluster.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef IDENTIFYCLUSTER_H_
#define IDENTIFYCLUSTER_H_

#include <memory>
#include "../Cluster.h"
#include "../attributeTypes/ZCLuint16Attribute.h"

namespace zigbee {

class IdentifyCluster : public Cluster {
public:
	IdentifyCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
public:
	virtual ClusterID getId() const override;
	virtual std::string getClusterName() const override;
public:
};

} /* namespace zigbee */

#endif /* IDENTIFYCLUSTER_H_ */
