/*
 * ResponseFile.h
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_RESPONSEFILE_H_
#define SRC_HTTPSERVER_RESTACTIONS_RESPONSEFILE_H_

#include "../RestParser/RestActions.h"

namespace zigbee {

class SingletonObjects;

namespace http {

class PlaceHolders;

class ResponseFile : public DefaultActionHandler {
public:
	ResponseFile(SingletonObjects & singletons) noexcept : singletons(singletons){};
	void operator()( Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
	SingletonObjects & singletons;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_RESPONSEFILE_H_ */