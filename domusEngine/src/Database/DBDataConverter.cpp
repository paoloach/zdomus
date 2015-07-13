/*
 * DBDataConverter.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/date_time.hpp>
#include <postgresql/server/postgres.h>
#include <postgresql/server/catalog/pg_type.h>
#include <boost/lexical_cast.hpp>
#include <libpq-fe.h>
#include <iostream>
#include <sstream>
#include "DBDataConverter.h"
#include "Exceptions/DBExceptionInvalidDataType.h"
#include <memory>

namespace zigbee {

using namespace boost::posix_time;
using namespace boost::gregorian;

DBDataConverter::~DBDataConverter() {
}

DBDataConverter::DBData::DBData(PGresult* result, uint rowIndex, uint colIndex) {
	type = PQftype(result, colIndex);
	modifier = PQfmod(result, colIndex);
	size = PQgetlength(result, rowIndex, colIndex);
	value = PQgetvalue(result, rowIndex, colIndex);
}

boost::any DBDataConverter::getAnyValue(const DBDataConverter::DBData& dbData) {
	switch (dbData.type) {
	case INT2OID:
	case INT4OID:
	case REGPROCOID:
	case OIDOID:
	case CASHOID:
		return boost::any(boost::lexical_cast<int32_t>(dbData.value));
	case NUMERICOID:
	case INT8OID:
		return boost::any(boost::lexical_cast<int64_t>(dbData.value));
	case FLOAT4OID:
	case FLOAT8OID:
		return boost::any(boost::lexical_cast<double>(dbData.value));
	case BOOLOID:

		if (dbData.value == "t" || dbData.value == "true" || dbData.value == "y" || dbData.value == "yes" || dbData.value == "on" || dbData.value == "1") {
			return boost::any(true);
		} else {
			return boost::any(false);
		}
	case CHAROID:
	case NAMEOID:
	case TEXTOID:
	case BPCHAROID:
	case VARCHAROID:
		return boost::any(boost::lexical_cast<std::string>(dbData.value));
	case ABSTIMEOID:
	case DATEOID:
	case TIMEOID:
	case TIMESTAMPTZOID:
	case TIMETZOID:
		return boost::any(boost::lexical_cast<std::string>(dbData.value));
	case TIMESTAMPOID:{
		std::string format("%Y-%m-%d %H:%M:%S%F%Q");

		std::unique_ptr<date_input_facet> date_input( new date_input_facet(format));
		std::unique_ptr<time_input_facet> time_input( new time_input_facet(format));


		std::stringstream stream(dbData.value);
		stream.imbue(std::locale(stream.getloc(), date_input.release()));
		stream.imbue(std::locale(stream.getloc(), time_input.release()));

		ptime timeStamp;
		stream >> timeStamp;
		return boost::any(timeStamp);
		}
	default:
		throw DBExceptionInvalidDataType(dbData.type);
	}
}

char* DBDataConverter::getStringValue(const boost::any value) {
	std::stringstream stream;

	if (value.type() == typeid(int32_t)) {
		stream << boost::any_cast<int32_t>(value);
	} else if (value.type() == typeid(int64_t)) {
		stream << boost::any_cast<int64_t>(value);
	} else if (value.type() == typeid(double)) {
		stream << boost::any_cast<double>(value);
	} else if (value.type() == typeid(double)) {
		stream << boost::any_cast<double>(value);
	} else if (value.type() == typeid(bool)) {
		stream << (boost::any_cast<bool>(value)  ? "t" : "f");
	} else if (value.type() == typeid(std::string)) {
		stream << boost::any_cast<std::string>(value);
	}
	return strdup(stream.str().c_str());
}

} /* namespace zigbee */
