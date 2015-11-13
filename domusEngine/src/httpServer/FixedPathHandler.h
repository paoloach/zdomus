/*
 * FixedPathHandler.h
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_FIXEDPATHHANDLER_H_
#define SRC_HTTPSERVER_FIXEDPATHHANDLER_H_

#include <string>
#include <Poco/Net/HTTPRequestHandler.h>

namespace zigbee {
namespace http {

class FixedPathHandler : public Poco::Net::HTTPRequestHandler {
public:
	FixedPathHandler(const std::string & value);
	virtual ~FixedPathHandler();
protected:
	virtual void handleRequest( Poco::Net::HTTPServerRequest & request,  Poco::Net::HTTPServerResponse & response) override;
private:
	std::string value;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_FIXEDPATHHANDLER_H_ */
