/*
 * RestActions.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include "RestActions.h"


namespace zigbee {
namespace http {


void RestActions::addActions(RestPath&& restPath, ActionHandler  f) noexcept{
	actions.emplace_back(std::move(restPath), std::move(f));
}

void RestActions::execute(PathReceived&& pathReceived, ServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	for (const auto & action: actions){
		if (std::get<0>(action) == pathReceived){
			std::get<1>(action)(PlaceHolders(std::get<0>(action), std::move(pathReceived)), request, response);
			return;
		}
	}
	defaultAction(request, response);
}

} /* namespace http */
} /* namespace zigbee */
