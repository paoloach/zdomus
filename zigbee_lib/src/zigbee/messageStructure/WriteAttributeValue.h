/*
 * WriteAttributeValue.h
 *
 *  Created on: 21/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef WRITEATTRIBUTEVALUE_H_
#define WRITEATTRIBUTEVALUE_H_

#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"
#include "../../zcl/ZCLDataType.h"

namespace zigbee {

#define MAX_WRITE_DATA_SIZE 12

struct __attribute__ ((__packed__)) WriteAttributeValueMsg {
	WriteAttributeValueMsg(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId, ZigbeeAttributeId attributeId, ZCLTypeDataType dataType,uint8_t dataValueLen, uint8_t * dataValue) noexcept:
	generticDataMsg {REQ_WRITE_ATTRIBUTE_VALUE},nwkAddr {nwkAddr.getId()},endpoint {endpointId.getId()},cluster {clusterId.getId()},attributeId {attributeId}, dataType{static_cast<ZigbeeAttributeDataType>(dataType)}, dataValueLen{dataValueLen} {
		memcpy(this->dataValue, dataValue, dataValueLen);
	}

	WriteAttributeValueMsg() :
			nwkAddr(0), endpoint(0), cluster(0), attributeId(0), dataType(0), dataValueLen(0) {
		generticDataMsg.msgCode = REQ_WRITE_ATTRIBUTE_VALUE;
	}
	GenericMessage generticDataMsg;
	ZigbeeNwkAddress nwkAddr;
	ZigbeeEndpoint endpoint;
	ZigbeeClusterId cluster;
	ZigbeeAttributeId attributeId;
	ZigbeeAttributeDataType dataType;
	uint8_t dataValueLen;
	uint8_t dataValue[MAX_WRITE_DATA_SIZE];
};

}

#endif /* WRITEATTRIBUTEVALUE_H_ */
