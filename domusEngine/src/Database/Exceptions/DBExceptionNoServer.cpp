/*
 * DBExceptionNoServer.cpp
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "DBExceptionNoServer.h"

namespace zigbee {

DBExceptionNoServer::DBExceptionNoServer(const std::string& address, const std::string& db) {
	std::stringstream stream;

	stream << "Unable to connect to database " << db << " on server " << address;
	message = stream.str();
}

DBExceptionNoServer::~DBExceptionNoServer() {
}

DBExceptionNoServer::DBExceptionNoServer(const std::string& address, const std::string& db, const std::string& cause) {
	std::stringstream stream;

	stream << "Unable to connect to database " << db << " on server " << address << " because: " << cause;
	message = stream.str();
}
} /* namespace zigbee */

