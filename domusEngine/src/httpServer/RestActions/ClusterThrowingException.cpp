/*
 * ClusterThrowingException.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zigbee/EndpointID.h>
#include <sstream>
#include <iostream>

#include "ClusterThrowingException.h"

namespace zigbee {
namespace http {

void ClusterThrowingException::throwWrongCluster(Poco::Net::HTTPServerResponse& response, const ClusterID& clusterId, const EndpointID& endpointId, const NwkAddr& nwkAddr) {
	std::stringstream message;

	message << "ERROR: " << "cluster " << clusterId << " is not an IN cluster of endpoint " << endpointId << " in the device with address " << nwkAddr << "\n";
	std::cerr << message.str() << std::endl;
	response.send() << message.str();
	response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
}

} /* namespace http */
} /* namespace zigbee */

