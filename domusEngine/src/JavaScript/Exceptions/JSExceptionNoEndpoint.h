/*
 * JSExceptionNoEndpoint.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTIONNOENDPOINT_H_
#define SRC_JAVASCRIPT_JSEXCEPTIONNOENDPOINT_H_

#include <zigbee/EndpointID.h>

#include "JSException.h"
#include "../../ZigbeeData/ExtAddress.h"

namespace zigbee {

class JSExceptionNoEndpoint: public JSException {
public:
	JSExceptionNoEndpoint(const ExtAddress & extAddress, EndpointID endpoint);
	virtual ~JSExceptionNoEndpoint();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTIONNOENDPOINT_H_ */
