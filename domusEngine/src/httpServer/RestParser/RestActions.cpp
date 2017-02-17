/*
 * RestActions.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/MediaType.h>
#include <boost/log/trivial.hpp>
#include "RestActions.h"


namespace zigbee {
namespace http {


void RestActions::addActions(RestPath&& restPath, ActionHandler  f) noexcept{
	actions.emplace_back(std::move(restPath), std::move(f));
}

void RestActions::execute(PathReceived&& pathReceived, ServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    if (fixedPathContainer != nullptr){
        auto result = fixedPathContainer->getValue(pathReceived);
        if (std::get<1>(result)){
            Poco::Net::MediaType mediaType("text","plain");
            response.setContentType(mediaType);
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

            response.send() << std::get<0>(result);
            return;
        }
    }
	for (const auto & action: actions){
		if (std::get<0>(action) == pathReceived){
            BOOST_LOG_TRIVIAL(info) << std::get<0>(action);
			std::get<1>(action)(PlaceHolders(std::get<0>(action), pathReceived), request, response);
			return;
		}
	}
	defaultAction(request, response);
}

} /* namespace http */
} /* namespace zigbee */
