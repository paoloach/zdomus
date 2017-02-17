/*
 * RestActions.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_
#define SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_

#include <utility>
#include <vector>
#include <tuple>
#include <functional>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "RestPath.h"
#include "PlaceHolders.h"
#include "PathReceived.h"
#include "../ServerRequest.h"
#include "../ExternalRestPath.h"

namespace zigbee {
namespace http {

using ActionHandler = std::function<void(const PlaceHolders &&, ServerRequest& request, Poco::Net::HTTPServerResponse& response)>;
using DefaultActionHandler = std::function<void(ServerRequest& request, Poco::Net::HTTPServerResponse& response)>;
using Actions = std::vector<std::tuple<RestPath, ActionHandler>> ;

class RestActions {
private:
	Actions actions;
	DefaultActionHandler defaultAction;
    ExternalRestPath  * fixedPathContainer;
public:
    RestActions(ExternalRestPath * fixedPathContainer):fixedPathContainer(fixedPathContainer){}
    RestActions(): fixedPathContainer(nullptr){}
	void addActions(RestPath && restPath,ActionHandler   f ) noexcept ;
	void setDefaultAction(DefaultActionHandler f) noexcept {defaultAction = std::move(f);}
	void execute(PathReceived &&pathReceived,  ServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_ */
