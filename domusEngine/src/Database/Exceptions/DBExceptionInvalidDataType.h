/*
 * DBExceptionInvalidDataType.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONINVALIDDATATYPE_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONINVALIDDATATYPE_H_

#include "DBException.h"

namespace zigbee {

class DBExceptionInvalidDataType: public DBException {
public:
	DBExceptionInvalidDataType(uint dataType);
	virtual ~DBExceptionInvalidDataType();
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTIONINVALIDDATATYPE_H_ */
