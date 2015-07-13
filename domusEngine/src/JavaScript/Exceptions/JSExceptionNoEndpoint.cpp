/*
 * JSExceptionNoEndpoint.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionNoEndpoint.h"

namespace zigbee {

JSExceptionNoEndpoint::JSExceptionNoEndpoint(const ExtAddress& extAddress, EndpointID endpoint) {
	std::stringstream stream;
	stream << "Unable to find endpoint " << endpoint << " on device with extended address " << extAddress;
	message = stream.str();
}

JSExceptionNoEndpoint::~JSExceptionNoEndpoint() {
}

} /* namespace zigbee */
