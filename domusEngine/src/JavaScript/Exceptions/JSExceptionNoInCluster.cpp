/*
 * JSExceptionNoInCluster.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSExceptionNoInCluster.h"
#include <sstream>

namespace zigbee {

JSExceptionNoInCluster::JSExceptionNoInCluster(const ExtAddress& extAddress, EndpointID endpoint, ClusterID clusterId) {
	std::stringstream stream;
	stream << "Unable to find input cluster " << clusterId << " in the endpoint " << endpoint << " of the device with extended address " << extAddress;
	message = stream.str();
}

JSExceptionNoInCluster::~JSExceptionNoInCluster() {
}

} /* namespace zigbee */
