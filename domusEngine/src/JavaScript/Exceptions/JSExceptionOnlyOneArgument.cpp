/*
 * JSExceptionOnlyOneArgument.cpp
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionOnlyOneArgument.h"

namespace zigbee {

JSExceptionOnlyOneArgument::JSExceptionOnlyOneArgument(const std::string& methodName) {
	std::stringstream stream;
	stream << "Unable to call method " << methodName << " because it need only one argument";
	message = stream.str();
}

JSExceptionOnlyOneArgument::~JSExceptionOnlyOneArgument() {
}

} /* namespace zigbee */
