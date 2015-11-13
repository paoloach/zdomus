/*
 * FixedPathHandler.cpp
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/MediaType.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "FixedPathHandler.h"


namespace zigbee {
namespace http {

FixedPathHandler::~FixedPathHandler() {
}

FixedPathHandler::FixedPathHandler(const std::string& value):value(value) {
}

void FixedPathHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	Poco::Net::MediaType mediaType("text","plain");
	response.setContentType(mediaType);
	response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

	std::ostream & stream = response.send();
	stream << "value";
}

} /* namespace http */
} /* namespace zigbee */
