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
#include "../attributeTypes/ZCLuint8Attribute.h"
#include "../attributeTypes/ZCLstringAttribute.h"
#include "../attributeTypes/ZCLbitmap8bitAttribute.h"
#include "../attributeTypes/ZCLbooleanAttribute.h"
#include "../attributeTypes/ZCLenum8bitAttribute.h"
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"


namespace zigbee {

class BasicCluster : public Cluster{
public:
	BasicCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
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
	virtual ClusterID getId();
	virtual std::string getClusterName();

};

} /* namespace zigbee */

#endif /* BASICCLUSTER_H_ */
