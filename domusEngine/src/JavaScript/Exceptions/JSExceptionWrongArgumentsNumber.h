/*
 * JSExceptionWrongArgumentsNumber.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONWRONGARGUMENTSNUMBER_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONWRONGARGUMENTSNUMBER_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionWrongArgumentsNumber : public JSException{
public:
	JSExceptionWrongArgumentsNumber(const std::string & instanceName, uint32_t argumentGot, uint32_t argumentExpected);
	virtual ~JSExceptionWrongArgumentsNumber();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONWRONGARGUMENTSNUMBER_H_ */
