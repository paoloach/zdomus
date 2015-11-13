/*
 * HttpServer.cpp
 *
 *  Created on: 07/apr/2015
 *      Author: Paolo Achdjian
 */



#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

#include "HttpServer.h"
#include "DEHttpRequestHandlerFactory.h"


namespace zigbee {
namespace http {

using namespace Poco::Net;

HttpServer::HttpServer(SingletonObjects & singletons) : singletons(singletons){
	requestFactory.reset( new DEHttpRequestHandlerFactory(singletons));
	Poco::UInt16 port = 8080;
	HTTPServerParams * params = new HTTPServerParams();
	params->setMaxQueued(100);
	params->setMaxThreads(3);

	Poco::Net::ServerSocket svs(port);

	server.reset(new Poco::Net::HTTPServer(requestFactory.get(), svs, params));
	server->start();

}

HttpServer::~HttpServer() {
	server->stop();
}

} /* namespace http */
} /* namespace zigbee */
