/*
 * JSExceptionArgNoInteger.cpp
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSExceptionArgNoInteger.h"

namespace zigbee {
    JSExceptionArgNoInteger::JSExceptionArgNoInteger(std::string &instanceName, uint32_t argumentIndex) {
        message = "Unable to create an instance of " + instanceName + " because the argument " + std::to_string(argumentIndex) + " must be an signed integer";
    }

    zigbee::JSExceptionArgNoInteger::JSExceptionArgNoInteger(const std::string &methodName) {
        message = "Invalid parameter: is request a signed integer to assign to attribute " + methodName;
    }

} /* namespace zigbee */
