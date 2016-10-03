/*
 * InvalidZDevice.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "InvalidZDevice.h"

namespace zigbee {

InvalidZDevice::InvalidZDevice(const ExtAddress& extAddress) {
	std::stringstream stream {};
	stream << "The device with extended address " << extAddress << " doesn't exist" << std::endl;
	message = stream.str();
}

InvalidZDevice::InvalidZDevice(NwkAddr shortAddress) {
	std::stringstream stream {};
	stream << "The device with network address " << shortAddress << " doesn't exist" << std::endl;
	message = stream.str();
}

InvalidZDevice::~InvalidZDevice() = default;

} /* namespace zigbee */


