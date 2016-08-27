/*
 * ResponseFile.cpp
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include "ResponseFile.h"

namespace zigbee {
namespace http {

void ResponseFile::operator ()( ServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	auto & uri = request.getURI();

	std::cout << "uri is : " << uri << std::endl;
	response.send() << "\n";

}

} /* namespace http */
} /* namespace zigbee */
