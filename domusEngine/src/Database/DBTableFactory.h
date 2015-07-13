/*
 * DBTableFactory.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBTABLEFACTORY_H_
#define SRC_DATABASE_DBTABLEFACTORY_H_

#include <string>

namespace zigbee {

class DBTable;

class DBTableFactory {
public:
	virtual ~DBTableFactory();
public:
	virtual DBTable * getTable(const std::string & tableName) const;
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBTABLEFACTORY_H_ */
