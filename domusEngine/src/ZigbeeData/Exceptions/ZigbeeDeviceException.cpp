/*
 * ZigbeeDeviceException.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include "ZigbeeDeviceException.h"

namespace zigbee {

ZigbeeDeviceException::ZigbeeDeviceException(const std::string& message):message(message) {
}

ZigbeeDeviceException::~ZigbeeDeviceException() {
}

const char* ZigbeeDeviceException::what() const noexcept{
	return message.c_str();
}

std::string ZigbeeDeviceException::getMessage() const {
	return message;
}

} /* namespace zigbee */
