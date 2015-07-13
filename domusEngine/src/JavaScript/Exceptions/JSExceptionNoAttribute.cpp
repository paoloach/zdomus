/*
 * JSExceptionNoAttribute.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionNoAttribute.h"

namespace zigbee {

JSExceptionNoAttribute::JSExceptionNoAttribute(const ExtAddress& extAddress, EndpointID endpoint, ClusterID clusterId, uint32_t attributeId) {
	std::stringstream stream;
	stream << "Invalid attribute " << attributeId << " for the cluster " << clusterId << " in the endpoint " << endpoint << " of the device with extended address " << extAddress;
	message = stream.str();
}

JSExceptionNoAttribute::~JSExceptionNoAttribute() {
}

} /* namespace zigbee */
