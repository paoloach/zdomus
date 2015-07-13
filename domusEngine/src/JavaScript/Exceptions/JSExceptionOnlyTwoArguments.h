/*
 * JSExceptionOnlyTwoArguments.h
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYTWOARGUMENTS_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYTWOARGUMENTS_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionOnlyTwoArguments : public JSException{
public:
	JSExceptionOnlyTwoArguments(const std::string & methodName);
	virtual ~JSExceptionOnlyTwoArguments();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYTWOARGUMENTS_H_ */
