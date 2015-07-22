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

class JSExceptionArgNoInteger: public JSException {
public:
	JSExceptionArgNoInteger(const std::string & instanceName, uint32_t argumentIndex);
	JSExceptionArgNoInteger(const std::string & methodName);
	virtual ~JSExceptionArgNoInteger();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOINTEGER_H_ */