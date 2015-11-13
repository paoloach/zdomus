/*
 * HTTPServerRequestMock.cpp
 *
 *  Created on: 13/apr/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "HTTPServerRequestMock.h"

namespace zigbee {
namespace http {
namespace test {

HTTPServerRequestMock::HTTPServerRequestMock(const std::string method, const std::string uri){
	setMethod(method);
	setURI(uri);
}

HTTPServerRequestMock::HTTPServerRequestMock() {
}

HTTPServerRequestMock::~HTTPServerRequestMock() {
}

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */
