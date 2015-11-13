/*
 * JSExceptionOnlyOneArgument.h
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYONEARGUMENT_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYONEARGUMENT_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionOnlyOneArgument: public JSException {
public:
	JSExceptionOnlyOneArgument(const std::string & methodName);
	virtual ~JSExceptionOnlyOneArgument();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONONLYONEARGUMENT_H_ */
