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

class DBExceptionNoServer : public DBException{
public:
	DBExceptionNoServer(const std::string & address, const std::string & db);
	DBExceptionNoServer(const std::string & address, const std::string & db, const std::string & cause);
	virtual ~DBExceptionNoServer();
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOSERVER_H_ */
