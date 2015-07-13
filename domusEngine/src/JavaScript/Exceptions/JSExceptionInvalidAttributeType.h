/*
 * JSExceptionInvalidAttributeType.h
 *
 *  Created on: 13/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONINVALIDATTRIBUTETYPE_H_
#define SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONINVALIDATTRIBUTETYPE_H_

#include "JSException.h"
#include <zcl/ZCLDataType.h>

namespace zigbee {

class JSExceptionInvalidAttributeType : public JSException {
public:
	JSExceptionInvalidAttributeType(const std::string & name, ZCLTypeDataType wrongType, ZCLTypeDataType rightType);
	virtual ~JSExceptionInvalidAttributeType();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_EXCEPTIONS_JSEXCEPTIONINVALIDATTRIBUTETYPE_H_ */
