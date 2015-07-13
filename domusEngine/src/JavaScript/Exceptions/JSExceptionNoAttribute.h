/*
 * JSExceptionNoAttribute.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTIONNOATTRIBUTE_H_
#define SRC_JAVASCRIPT_JSEXCEPTIONNOATTRIBUTE_H_

#include "JSException.h"
#include "../../ZigbeeData/ExtAddress.h"
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>

namespace zigbee {

class JSExceptionNoAttribute : public JSException {
public:
	JSExceptionNoAttribute(const ExtAddress & extAddress, EndpointID endpoint, ClusterID clusterId, uint32_t attributeId);
	virtual ~JSExceptionNoAttribute();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTIONNOATTRIBUTE_H_ */
