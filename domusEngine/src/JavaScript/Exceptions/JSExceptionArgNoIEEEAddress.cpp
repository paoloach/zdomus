/*
 * JSExceptionArgNoIEEEAddress.cpp
 *
 *  Created on: 15/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>

#include "JSExceptionArgNoIEEEAddress.h"

namespace zigbee {

JSExceptionArgNoIEEEAddress::JSExceptionArgNoIEEEAddress() {
	std::stringstream stream;
	stream << "Invalid parameter: is request a string of format 'hh-hh-hh-hh-hh-hh-hh-hh'";
	message = stream.str();
}

JSExceptionArgNoIEEEAddress::JSExceptionArgNoIEEEAddress(const std::string & wrongArg) {
	std::stringstream stream;
	stream << "Invalid parameter: is request a string of format 'hh-hh-hh-hh-hh-hh-hh-hh' but got " << wrongArg;
	message = stream.str();
}

JSExceptionArgNoIEEEAddress::~JSExceptionArgNoIEEEAddress() {
}

} /* namespace zigbee */
