/*
 * ComandSend.h
 *
 *  Created on: 05/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef COMANDSEND_H_
#define COMANDSEND_H_

#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"

namespace zigbee {

#define MAX_CLUSTERS 20
static const int HEADER_SIZE = sizeof(GenericMessage) + sizeof(ZigbeeNwkAddress) + sizeof(ZigbeeEndpoint) + sizeof(ZigbeeClusterId) + sizeof(ZigbeeClusterCmdId) + sizeof(uint8_t);
static const int MAX_DATA_SIZE = 64;

struct __attribute__ ((__packed__)) ComandSend {
	ComandSend(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId, ZigbeeClusterCmdId cmdId, const std::vector<uint8_t> & data) noexcept:
	generticDataMsg {REQ_SEND_CMD_VALUES},nwkAddr {nwkAddr.getId()},endpoint {endpointId.getId()},cluster {clusterId.getId()},cmdId {cmdId} {
		dataLen = data.size();
		memcpy(this->data, &(*data.begin()), data.size());
	}

	GenericMessage generticDataMsg;
	ZigbeeNwkAddress nwkAddr;
	ZigbeeEndpoint endpoint;
	ZigbeeClusterId cluster;
	ZigbeeClusterCmdId cmdId;
	uint8_t dataLen;
	uint8_t data[MAX_DATA_SIZE];
};

}

#endif /* COMANDSEND_H_ */
