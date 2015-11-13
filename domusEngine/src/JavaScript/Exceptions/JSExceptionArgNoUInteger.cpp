/*
 * JSExceptionArgNoUInteger.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */
#include <sstream>
#include "JSExceptionArgNoUInteger.h"

namespace zigbee {

JSExceptionArgNoUInteger::JSExceptionArgNoUInteger(const std::string& instanceName, uint32_t argumentIndex) {
	std::stringstream stream;
	stream << "Unable to create an instance of " << instanceName << " because the argument " << argumentIndex << " must be an unsigned integer";
	message = stream.str();
}

JSExceptionArgNoUInteger::~JSExceptionArgNoUInteger() {
}
zigbee::JSExceptionArgNoUInteger::JSExceptionArgNoUInteger(const std::string & methodName) {
	std::stringstream stream;
	stream << "Invalid parameter: is request a unsigned integer to assign to attribute " << methodName;
	message = stream.str();
}

} /* namespace zigbee */

