/*
 * JSExceptionArgNoString.cpp
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionArgNoString.h"

namespace zigbee {

JSExceptionArgNoString::JSExceptionArgNoString(const std::string& instanceName, uint32_t argumentIndex, bool construct) {
	std::stringstream stream;
	if (construct){
		stream << "Unable to create an instance of " << instanceName << " because the argument " << argumentIndex << " must be a string";
	} else {
		stream << "The " << argumentIndex << " of method " << instanceName << " should be a string";
	}
	message = stream.str();
}

JSExceptionArgNoString::JSExceptionArgNoString(const std::string& methodName) {
	std::stringstream stream;
	stream << "Invalid parameter: is request a string to assign to attribute " << methodName;
	message = stream.str();
}

JSExceptionArgNoString::~JSExceptionArgNoString() {
}

} /* namespace zigbee */
