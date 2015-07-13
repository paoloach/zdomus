/*
 * DBTableFactory.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include "DBTableFactory.h"
#include "DBTable.h"

namespace zigbee {

DBTableFactory::~DBTableFactory() {
}

DBTable* DBTableFactory::getTable(const std::string& tableName) const {
	return new DBTable(tableName);
}

} /* namespace zigbee */
