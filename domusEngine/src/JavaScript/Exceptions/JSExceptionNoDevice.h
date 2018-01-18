/*
 * JSExceptionNoDevice.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTIONNODEVICE_H_
#define SRC_JAVASCRIPT_JSEXCEPTIONNODEVICE_H_

#include "JSException.h"
#include <zigbee/ExtAddress.h>

namespace zigbee {

class JSExceptionNoDevice: public JSException {
public:
	JSExceptionNoDevice(const ExtAddress & extAddress);
	virtual ~JSExceptionNoDevice();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTIONNODEVICE_H_ */
