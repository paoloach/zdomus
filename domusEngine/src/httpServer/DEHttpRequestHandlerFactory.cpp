/*
 * DEHttpRequestHandlerFactory.cpp
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerRequest.h>
#include <boost/filesystem/path.hpp>
#include <iostream>

#include "DEHttpRequestHandlerFactory.h"
#include "FixedPathHandler.h"
#include "DeviceBrowserHandler.h"
#include "../Utils/SingletonObjects.h"
#include "ExternalRestPath.h"

namespace zigbee {
namespace http {

using Poco::Net::HTTPRequestHandler;

DEHttpRequestHandlerFactory::DEHttpRequestHandlerFactory(SingletonObjects & singletons) :
		singletons(singletons) {

}

HTTPRequestHandler* DEHttpRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& ) {
	return new DeviceBrowserHandler(singletons);
}

} /* namespace http */
} /* namespace zigbee */
