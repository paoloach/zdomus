/*
 * JSExceptionOutOfRange.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONOUTOFRANGE_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONOUTOFRANGE_H_

#include "JSException.h"

namespace zigbee {

class JSExceptionOutOfRange : public JSException{
public:
	JSExceptionOutOfRange(int32_t, int64_t min, int64_t max);
	virtual ~JSExceptionOutOfRange();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONOUTOFRANGE_H_ */
