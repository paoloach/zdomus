/*
 * DBExceptionQueryError.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include "DBExceptionQueryError.h"

namespace zigbee {

DBExceptionQueryError::DBExceptionQueryError(const std::string& query, const std::string& tableName,const std::string & cause) {
	message = "Unable to executer query " + query + " on table " + tableName + " because " + cause;
}

DBExceptionQueryError::~DBExceptionQueryError() {
}

} /* namespace zigbee */
