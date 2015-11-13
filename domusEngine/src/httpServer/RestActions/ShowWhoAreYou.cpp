/*
 * ShowWhoAreYou.cpp
 *
 *  Created on: 18/lug/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/MediaType.h>

#include "ShowWhoAreYou.h"

namespace zigbee {
namespace http {

void zigbee::http::ShowWhoAreYou::operator ()(const PlaceHolders&& , Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& response) {
	Poco::Net::MediaType mediaType("text", "plain");
	response.setContentType(mediaType);
	response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

	std::ostream & stream = response.send();
	stream << "I am DomusEngine version 1.0.0";
}

} /* namespace http */
} /* namespace zigbee */

