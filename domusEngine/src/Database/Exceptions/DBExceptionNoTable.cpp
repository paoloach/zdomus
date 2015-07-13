/*
 * DBExceptionNoTable.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "DBExceptionNoTable.h"

namespace zigbee {

DBExceptionNoTable::DBExceptionNoTable(const std::string& address, const std::string& db, const std::string& tableName) {
	std::stringstream stream;

	stream << "Unable to find table " << tableName << " on database " << db << " of server " << address;
	message = stream.str();
}

DBExceptionNoTable::~DBExceptionNoTable() {
}

} /* namespace zigbee */
