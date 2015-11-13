/*
 * JSExceptionWrongArgumentsNumber.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */
#include <sstream>
#include "JSExceptionWrongArgumentsNumber.h"

namespace zigbee {

JSExceptionWrongArgumentsNumber::JSExceptionWrongArgumentsNumber(const std::string& instanceName, uint32_t argumentGot, uint32_t argumentExpected) {
	std::stringstream stream;
	stream << "Unable to create an instance of " << instanceName << " because it is need " << argumentExpected << " parameters but got " << argumentGot;
	message = stream.str();
}

JSExceptionWrongArgumentsNumber::~JSExceptionWrongArgumentsNumber() {
	// TODO Auto-generated destructor stub
}

} /* namespace zigbee */
