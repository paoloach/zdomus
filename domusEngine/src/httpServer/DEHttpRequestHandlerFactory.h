/*
 * DEHttpRequestHandlerFactory.h
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_DEHTTPREQUESTHANDLERFACTORY_H_
#define SRC_HTTPSERVER_DEHTTPREQUESTHANDLERFACTORY_H_

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "RestParser/RestActions.h"


namespace zigbee {

class SingletonObjects;


namespace http {


class DEHttpRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory{
public:
	DEHttpRequestHandlerFactory(SingletonObjects & singletons);
protected:
	virtual Poco::Net::HTTPRequestHandler *  createRequestHandler(const Poco::Net::HTTPServerRequest & request) override;
protected:
	SingletonObjects & singletons;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_DEHTTPREQUESTHANDLERFACTORY_H_ */
