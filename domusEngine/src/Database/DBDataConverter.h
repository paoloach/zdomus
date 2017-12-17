/*
 * DBDataConverter.h
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBDATACONVERTER_H_
#define SRC_DATABASE_DBDATACONVERTER_H_

#include <libpq-fe.h>
#include <any>
#include <string>
#include "ResultSet.h"

namespace zigbee {

class DBDataConverter {
public:
	class DBData {
	public:
		DBData(ResultSet * result, int rowIndex, int colIndex);
	public:
		Oid type;
		int modifier;
		std::string_view value;
        ResultSet::FORMAT_CODE  formatCode;
	};
public:
	virtual ~DBDataConverter() = default;
	static std::any getAnyValue(const DBDataConverter::DBData & dbData);
	static char * getStringValue(const std::any value);
};

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBDATACONVERTER_H_ */
