/*
 * BasicCluster.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef BASICCLUSTER_H_
#define BASICCLUSTER_H_

#include <string>
#include <memory>
#include "zcl/impl/ClusterImpl.h"
#include "../../zigbee/ZigbeeDevice.h"


namespace zigbee {

class BasicCluster : public ClusterImpl{
public:
	BasicCluster(ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
public:
	enum PowerSourceType {
		Unknow =0,
		MainSinglePhase=1,
		MainsThreePhase=2,
		Battery=3,
		DCSource=4,
		EmergencyMainConstPowerd=5,
		EmergencyMainTransSwitch=6
	};
	ClusterID getId() const override;
	std::string getClusterName() const override ;

};

} /* namespace zigbee */

#endif /* BASICCLUSTER_H_ */
