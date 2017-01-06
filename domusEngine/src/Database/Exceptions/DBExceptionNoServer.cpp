/*
 * DBExceptionNoServer.cpp
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#include "DBExceptionNoServer.h"

namespace zigbee {

    DBExceptionNoServer::DBExceptionNoServer() {
        message = "Unable to connect to database";
    }

    DBExceptionNoServer::DBExceptionNoServer(const std::string &cause) {
        message = "Unable to connect to database because: " + cause;
    }

    DBExceptionNoServer::DBExceptionNoServer(const std::string &server, const std::string &dbName, const std::string &cause) {
        message = "Unable to connect to database " + dbName + " at " + server + " because: " + cause;
    }

    DBExceptionNoServer::DBExceptionNoServer(const std::string &server, const std::string &dbName) {
        message = "Unable to connect to database " + dbName + " at " + server;
    }
} /* namespace zigbee */

