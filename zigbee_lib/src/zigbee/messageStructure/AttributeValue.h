/*
 * AttributeValue.h
 *
 *  Created on: 05/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTEVALUE_H_
#define ATTRIBUTEVALUE_H_

#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"

namespace zigbee {

#define MAX_CLUSTERS 20

struct __attribute__ ((__packed__)) AttributeValue {
	AttributeValue(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId, ZigbeeAttributeId attribute) noexcept:
			generticDataMsg{REQ_ATTRIBUTE_VALUES},nwkAddr{nwkAddr.getId()},endpoint{endpointId.getId()},cluster{clusterId.getId()},attribute{attribute} {

	}

	AttributeValue():nwkAddr(0),endpoint(0),cluster(0),attribute(0) {
		generticDataMsg.msgCode = REQ_ATTRIBUTE_VALUES;
	}

	GenericMessage generticDataMsg;
	ZigbeeNwkAddress nwkAddr;
	ZigbeeEndpoint endpoint;
	ZigbeeClusterId cluster;
	ZigbeeAttributeId attribute;
};

}

#endif /* ATTRIBUTEVALUE_H_ */
