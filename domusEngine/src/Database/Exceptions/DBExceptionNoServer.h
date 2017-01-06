/*
 * DBExceptionNoServer.h
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOSERVER_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOSERVER_H_

#include "DBException.h"

namespace zigbee {

    class DBExceptionNoServer : public DBException {
    public:
        DBExceptionNoServer();

        DBExceptionNoServer(const std::string &cause);

        DBExceptionNoServer(const std::string &server, const std::string &dbName, const std::string &cause);

        DBExceptionNoServer(const std::string &server, const std::string &dbName);

        virtual ~DBExceptionNoServer() noexcept = default;
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOSERVER_H_ */
