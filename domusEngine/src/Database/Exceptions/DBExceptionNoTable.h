/*
 * DBExceptionNoTable.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOTABLE_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOTABLE_H_

#include "DBException.h"

namespace zigbee {

class DBExceptionNoTable: public DBException {
public:
	DBExceptionNoTable(const std::string & address, const std::string & db, const std::string & tableName);
	virtual ~DBExceptionNoTable();

};

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONNOTABLE_H_ */
