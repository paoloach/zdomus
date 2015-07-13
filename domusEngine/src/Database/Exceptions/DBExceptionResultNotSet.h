/*
 * DBExceptionResultNotSet.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONRESULTNOTSET_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONRESULTNOTSET_H_

#include "DBException.h"

namespace zigbee {

class DBExceptionResultNotSet: public DBException {
public:
	DBExceptionResultNotSet(const std::string & tableName);
	virtual ~DBExceptionResultNotSet();
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONRESULTNOTSET_H_ */
