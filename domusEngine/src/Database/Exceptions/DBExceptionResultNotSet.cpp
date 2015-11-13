/*
 * DBExceptionResultNotSet.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include "DBExceptionResultNotSet.h"

namespace zigbee {

DBExceptionResultNotSet::DBExceptionResultNotSet(const std::string& tableName) {
	message = "The resultSet for table " + tableName + " is not set. Use first find";
}

DBExceptionResultNotSet::~DBExceptionResultNotSet() {
}

} /* namespace zigbee */
