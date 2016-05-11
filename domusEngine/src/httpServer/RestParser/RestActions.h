/*
 * RestActions.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_
#define SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_

#include <vector>
#include <tuple>
#include <functional>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "RestPath.h"
#include "PlaceHolders.h"
#include "PathReceived.h"

namespace zigbee {
namespace http {

using ActionHandler = std::function<void(const PlaceHolders &&, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)>;
using DefaultActionHandler = std::function<void(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)>;
using Actions = std::vector<std::tuple<RestPath, ActionHandler>> ;

class RestActions {
private:
	Actions actions;
	DefaultActionHandler defaultAction;
public:
	void addActions(RestPath && restPath,ActionHandler   f ) noexcept ;
	void setDefaultAction(DefaultActionHandler f) noexcept {defaultAction = f;}
	void execute(PathReceived &&pathReceived,  Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_RESTACTIONS_H_ */
