/*
 * ClusterThrowingException.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_CLUSTERTHROWINGEXCEPTION_H_
#define SRC_HTTPSERVER_RESTACTIONS_CLUSTERTHROWINGEXCEPTION_H_

namespace zigbee {

class EndpointID;
class ClusterID;
class NwkAddr;

namespace http {

class ClusterThrowingException {
public:
	void throwWrongCluster(Poco::Net::HTTPServerResponse& response, const ClusterID & clusterId, const EndpointID&  endpointId, const NwkAddr & nwkAddr);
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_CLUSTERTHROWINGEXCEPTION_H_ */