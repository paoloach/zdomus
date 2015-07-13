/*
 * JSExceptionOnlyTwoArguments.cpp
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionOnlyTwoArguments.h"

namespace zigbee {

JSExceptionOnlyTwoArguments::JSExceptionOnlyTwoArguments(const std::string& methodName) {
	std::stringstream stream;
	stream << "Unable to call method " << methodName << " because it need two arguments";
	message = stream.str();
}

JSExceptionOnlyTwoArguments::~JSExceptionOnlyTwoArguments() {
}

} /* namespace zigbee */
