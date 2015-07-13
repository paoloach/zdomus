/*
 * JSExceptionArgNoExtAddress.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOEXTADDRESS_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOEXTADDRESS_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionArgNoExtAddress : public JSException{
public:
	JSExceptionArgNoExtAddress(const std::string & instanceName, uint32_t argumentIndex);
	virtual ~JSExceptionArgNoExtAddress();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONARGNOEXTADDRESS_H_ */
