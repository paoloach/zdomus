/*
 * JSException.cpp
 *
 *  Created on: 06/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSException.h"

namespace zigbee {


JSException::JSException(const std::string& message):message(message) {
}

JSException::~JSException() {
}

const char* JSException::what() const _GLIBCXX_USE_NOEXCEPT {
	return message.c_str();
}

} /* namespace zigbee */
