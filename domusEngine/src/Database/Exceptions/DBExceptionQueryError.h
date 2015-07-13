/*
 * DBExceptionQueryError.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONQUERYERROR_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONQUERYERROR_H_

#include "DBException.h"

namespace zigbee {

class DBExceptionQueryError: public DBException {
public:
	DBExceptionQueryError(const std::string & query, const std::string & tableName,const std::string & cause);
	virtual ~DBExceptionQueryError();
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONQUERYERROR_H_ */
