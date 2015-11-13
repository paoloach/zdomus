/*
 * JSExceptionArgNoBool.h
 *
 *  Created on: 15/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOBOOL_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOBOOL_H_

#include "JSException.h"
namespace zigbee {

class JSExceptionArgNoBool : public JSException{
public:
	JSExceptionArgNoBool();
	virtual ~JSExceptionArgNoBool();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOBOOL_H_ */
