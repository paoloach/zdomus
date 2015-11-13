/*
 * DBDataConverter.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBDATACONVERTER_H_
#define SRC_DATABASE_DBDATACONVERTER_H_

#include <libpq-fe.h>
#include <boost/any.hpp>

namespace zigbee {

class DBDataConverter {
public:
	class DBData {
	public:
		DBData(PGresult * result, uint rowIndex, uint colIndex);
	public:
		Oid type;
		int modifier;
		int size;
		std::string value;
	};
public:
	virtual ~DBDataConverter();
	static boost::any getAnyValue(const DBDataConverter::DBData & dbData);
	static char * getStringValue(const boost::any value);
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBDATACONVERTER_H_ */
