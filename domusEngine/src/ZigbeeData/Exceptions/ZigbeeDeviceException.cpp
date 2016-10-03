/*
 * ZigbeeDeviceException.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include <utility>

#include "ZigbeeDeviceException.h"

namespace zigbee {

ZigbeeDeviceException::ZigbeeDeviceException(std::string  message):message(std::move(message)) {
}

ZigbeeDeviceException::~ZigbeeDeviceException() = default;
const char* ZigbeeDeviceException::what() const noexcept{
	return message.c_str();
}

std::string ZigbeeDeviceException::getMessage() const {
	return message;
}

} /* namespace zigbee */
