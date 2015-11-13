/*
 * JSExceptionNoInCluster.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTIONNOINCLUSTER_H_
#define SRC_JAVASCRIPT_JSEXCEPTIONNOINCLUSTER_H_

#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include "JSException.h"
#include "../../ZigbeeData/ExtAddress.h"

namespace zigbee {

class JSExceptionNoInCluster: public JSException {
public:
	JSExceptionNoInCluster(const ExtAddress & extAddress, EndpointID endpoint, ClusterID clusterId);
	virtual ~JSExceptionNoInCluster();
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTIONNOINCLUSTER_H_ */
