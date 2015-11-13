/*
 * JSExceptionArgNoFunction.h
 *
 *  Created on: 04/feb/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOFUNCTION_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOFUNCTION_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionArgNoFunction  : public JSException {
public:
	JSExceptionArgNoFunction(uint32_t index);
	virtual ~JSExceptionArgNoFunction();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOFUNCTION_H_ */
