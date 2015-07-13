/*
 * PathElement.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include "PathElement.h"

namespace zigbee {
namespace http {


PathElement::PathElement(const std::string& value) noexcept {
	auto size = value.size();
	auto firstChar = value[0];
	auto lastChar = value[size-1];
	if (firstChar == '{' && lastChar=='}'){
		placeholder = true;
		this->value = value.substr(1, size-2);
	} else {
		placeholder = false;
		this->value = value;
	}
}


} /* namespace http */
} /* namespace zigbee */
