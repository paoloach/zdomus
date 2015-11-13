/*
 * JSExceptionArgNoBool.cpp
 *
 *  Created on: 15/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>

#include "JSExceptionArgNoBool.h"

namespace zigbee {

JSExceptionArgNoBool::JSExceptionArgNoBool() {
	std::stringstream stream;
	stream << "Invalid parameter: expected an argument of type boolean";
	message = stream.str();

}

JSExceptionArgNoBool::~JSExceptionArgNoBool() {
}

} /* namespace zigbee */
