/*
 * JSExceptionArgNoInteger.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOINTEGER_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOINTEGER_H_

#include "JSException.h"

namespace zigbee {

    class JSExceptionArgNoInteger : public JSException {
    public:
        JSExceptionArgNoInteger(std::string &instanceName, uint32_t argumentIndex);
        JSExceptionArgNoInteger(std::string &&instanceName, uint32_t argumentIndex){
            message = "Unable to create an instance of " + instanceName + " because the argument " + std::to_string(argumentIndex) + " must be an signed integer";
        }
        JSExceptionArgNoInteger(const std::string &methodName);

        virtual ~JSExceptionArgNoInteger()=default;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOINTEGER_H_ */
