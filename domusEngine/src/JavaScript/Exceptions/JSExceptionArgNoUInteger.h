/*
 * JSExceptionArgNoUInteger.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOUINTEGER_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOUINTEGER_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionArgNoUInteger: public JSException {
public:
	JSExceptionArgNoUInteger(const std::string & instanceName, uint32_t argumentIndex);
	JSExceptionArgNoUInteger(const std::string & methodName);
	virtual ~JSExceptionArgNoUInteger();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOUINTEGER_H_ */
