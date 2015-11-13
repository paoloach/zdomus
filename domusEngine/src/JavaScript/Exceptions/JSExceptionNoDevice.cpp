/*
 * JSExceptionNoDevice.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionNoDevice.h"

namespace zigbee {


JSExceptionNoDevice::JSExceptionNoDevice(const ExtAddress& extAddress) {
	std::stringstream stream;
	stream << "Unable to find zDevice " << extAddress;
	message = stream.str();
}

JSExceptionNoDevice::~JSExceptionNoDevice() {
}

} /* namespace zigbee */
