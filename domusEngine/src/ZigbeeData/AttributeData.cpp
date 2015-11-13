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

AttributeData::AttributeData(const ReadAttributeResponseMessage& attribute) {
	type = attribute.type;
	clusterId = attribute.clusterId;
	networkAddr = attribute.networkAddr;
	endpoint = attribute.endpoint;
	panId = attribute.panId;
	attrID = attribute.attrID;
	status = attribute.status;

	std::copy(attribute.data, attribute.data+attribute.dataLen, std::back_inserter(data));
}

AttributeData & AttributeData::operator =(const ReadAttributeResponseMessage& attribute) {
	type = attribute.type;
	clusterId = attribute.clusterId;
	networkAddr = attribute.networkAddr;
	endpoint = attribute.endpoint;
	panId = attribute.panId;
	attrID = attribute.attrID;
	status = attribute.status;
	std::copy(attribute.data, attribute.data+attribute.dataLen, std::back_inserter(data));
	return *this;
}

AttributeData::~AttributeData() {
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
