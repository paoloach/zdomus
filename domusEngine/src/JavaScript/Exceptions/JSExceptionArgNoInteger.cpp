/*
 * JSExceptionArgNoInteger.cpp
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionArgNoInteger.h"

namespace zigbee {

JSExceptionArgNoInteger::JSExceptionArgNoInteger(const std::string& instanceName, uint32_t argumentIndex) {
	std::stringstream stream;
	stream << "Unable to create an instance of " << instanceName << " because the argument " << argumentIndex << " must be an signed integer";
	message = stream.str();
}

JSExceptionArgNoInteger::~JSExceptionArgNoInteger() {
}
zigbee::JSExceptionArgNoInteger::JSExceptionArgNoInteger(const std::string & methodName) {
	std::stringstream stream;
	stream << "Invalid parameter: is request a signed integer to assign to attribute " << methodName;
	message = stream.str();
}

} /* namespace zigbee */
