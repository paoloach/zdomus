/*
 * JSExceptionArgNoString.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOSTRING_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOSTRING_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionArgNoString : public JSException{
public:
	JSExceptionArgNoString(const std::string & instanceName, uint32_t argumentIndex, bool construct=true);
	JSExceptionArgNoString(const std::string & methodName);
	virtual ~JSExceptionArgNoString();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOSTRING_H_ */
