/*
 * AttributeData.cpp
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#include <algorithm>
#include <iostream>
#include "AttributeData.h"

namespace zigbee {

AttributeData::AttributeData() {

}

AttributeData::AttributeData(const ReadAttributeResponseMessage& attribute, AttributeResponse & attributeResponse, size_t attributeLen) {
	type = attribute.type;
	clusterId = attribute.clusterId;
	networkAddr = attribute.networkAddr;
	endpoint = attribute.endpoint;
	panId = attribute.panId;
	attrID = attributeResponse.attrID;
	status = attributeResponse.status;

	uint8_t * rawData = reinterpret_cast<uint8_t *>(&attributeResponse)+sizeof(AttributeResponse);
	std::copy(rawData, rawData+attributeLen, std::back_inserter(data));
}


bool AttributeData::operator==(const AttributeData & other) {
	return (type == other.type) && (clusterId == other.clusterId) &&
			(networkAddr == other.networkAddr) &&
			(endpoint == other.endpoint) &&
			(panId == other.panId) &&
			(attrID == other.attrID) &&
			(status == other.status) &&
			(data == other.data);
}

} /* namespace zigbee */
