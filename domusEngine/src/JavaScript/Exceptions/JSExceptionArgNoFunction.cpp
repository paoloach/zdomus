/*
 * JSExceptionArgNoFunction.cpp
 *
 *  Created on: 04/feb/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSExceptionArgNoFunction.h"

namespace zigbee {

JSExceptionArgNoFunction::JSExceptionArgNoFunction(uint32_t index) {
	std::stringstream stream;

	stream << "the argument " << index << "-th should be a function";
	message =stream.str();

}

JSExceptionArgNoFunction::~JSExceptionArgNoFunction() {
}

} /* namespace zigbee */
