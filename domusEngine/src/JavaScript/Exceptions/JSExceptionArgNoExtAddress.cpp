/*
 * JSExceptionArgNoExtAddress.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>

#include "JSExceptionArgNoExtAddress.h"

namespace zigbee {

JSExceptionArgNoExtAddress::JSExceptionArgNoExtAddress(const std::string & instanceName, uint32_t argumentIndex) {
	std::stringstream stream;
	stream << "Unable to create an instance of " << instanceName << " because the argument " << argumentIndex << " must be a string representing a valid extended address";
	message = stream.str();
}

JSExceptionArgNoExtAddress::~JSExceptionArgNoExtAddress() {
}

} /* namespace zigbee */
