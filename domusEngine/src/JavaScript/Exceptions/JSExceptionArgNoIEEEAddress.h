/*
 * JSExceptionArgNoIEEEAddress.h
 *
 *  Created on: 15/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOIEEEADDRESS_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOIEEEADDRESS_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionArgNoIEEEAddress : public JSException{
public:
	JSExceptionArgNoIEEEAddress();
	JSExceptionArgNoIEEEAddress(const std::string & wrongArg);
	virtual ~JSExceptionArgNoIEEEAddress();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOIEEEADDRESS_H_ */
