/*
 * HttpServer.h
 *
 *  Created on: 07/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_HTTPSERVER_H_
#define SRC_HTTPSERVER_HTTPSERVER_H_

#include <memory>
#include <Poco/Net/HTTPServer.h>
#include "DEHttpRequestHandlerFactory.h"
#include "FixedPathContainer.h"
#include "../ZigbeeData/ZDevices.h"
#include <zcl/ClusterTypeFactory.h>
#include "../Utils/SingletonObjects.h"

namespace zigbee {
namespace http {

class HttpServer {
public:
	HttpServer( SingletonObjects & singletons);
	virtual ~HttpServer();
private:
	std::unique_ptr<DEHttpRequestHandlerFactory> requestFactory;
	std::unique_ptr<Poco::Net::HTTPServer> server;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_HTTPSERVER_H_ */
