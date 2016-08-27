/*
 * ShowHello.cpp
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/MediaType.h>

#include "ShowHello.h"

namespace zigbee {
    namespace http {

        void ShowHello::operator()(const PlaceHolders &&, ServerRequest &, Poco::Net::HTTPServerResponse &response) {
            Poco::Net::MediaType mediaType("text", "plain");
            response.setContentType(mediaType);
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

            response.send() << "Hello\n";
        }

    } /* namespace http */
} /* namespace zigbee */

