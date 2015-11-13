/*
 * JSExceptionOutOfRange.cpp
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionOutOfRange.h"

namespace zigbee {

JSExceptionOutOfRange::JSExceptionOutOfRange(int32_t value, int64_t min, int64_t max) {
	std::stringstream stream;
	stream << "value " << value << " is out of range [" << min << " - " << max << "]";
	message = stream.str();
}

JSExceptionOutOfRange::~JSExceptionOutOfRange() {
}

} /* namespace zigbee */
