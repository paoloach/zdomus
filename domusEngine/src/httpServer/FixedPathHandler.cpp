/*
 * FixedPathHandler.cpp
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/MediaType.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <utility>
#include "FixedPathHandler.h"


namespace zigbee {
    namespace http {

        FixedPathHandler::~FixedPathHandler() = default;

        FixedPathHandler::FixedPathHandler(std::string value) : value(std::move(value)) {
        }

        void FixedPathHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &response) {
            Poco::Net::MediaType mediaType("text", "plain");
            response.setContentType(mediaType);
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

            std::ostream &stream = response.send();
            stream << "value";
        }

    } /* namespace http */
} /* namespace zigbee */
