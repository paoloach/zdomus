/*
 * DBDataConverter.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <boost/date_time.hpp>
#include <boost/any.hpp>
#include <postgres.h>
#include <catalog/pg_type.h>
#include <libpq-fe.h>
#include "DBDataConverter.h"
#include "Exceptions/DBExceptionInvalidDataType.h"

namespace zigbee {

using namespace boost::posix_time;
using namespace boost::gregorian;
using std::any;
using std::any_cast;


DBDataConverter::DBData::DBData(ResultSet * result, int rowIndex, int colIndex) {
	type = result->getFieldType(colIndex);
	modifier = result->getModifier(colIndex);
    formatCode = result->getFormatCode(colIndex);
    value = result->getRawValue(colIndex,rowIndex);
}

std::any DBDataConverter::getAnyValue(const DBDataConverter::DBData& dbData) {
	switch (dbData.type) {
	case INT2OID:
	case INT4OID:
	case REGPROCOID:
	case OIDOID:
	case CASHOID:
        if (dbData.formatCode == ResultSet::BINARY)
		    return any(boost::lexical_cast<int32_t>(dbData.value));
        else
            return any(std::atoi(dbData.value.data()));
	case NUMERICOID:
	case INT8OID:
        if (dbData.formatCode == ResultSet::BINARY)
		    return any(boost::lexical_cast<int64_t>(dbData.value));
        else
            return any(std::atoll(dbData.value.data()));
	case FLOAT4OID:
	case FLOAT8OID:
        if (dbData.formatCode == ResultSet::BINARY)
		    return any(boost::lexical_cast<double>(dbData.value));
        else
            return any(std::atof(dbData.value.data()));
	case BOOLOID:
        if (dbData.formatCode == ResultSet::BINARY)
            if (dbData.value.data()[0] == 0)
                return any(false);
            else
                return any(true);
        else
		    if (dbData.value == "t" || dbData.value == "true" || dbData.value == "y" || dbData.value == "yes" || dbData.value == "on" || dbData.value == "1") {
			    return any(true);
		    } else {
			    return any(false);
		    }
	case CHAROID:
	case NAMEOID:
	case TEXTOID:
	case BPCHAROID:
	case VARCHAROID:
		return any(boost::lexical_cast<std::string>(dbData.value));
	case ABSTIMEOID:
	case DATEOID:
	case TIMEOID:
	case TIMESTAMPTZOID:
	case TIMETZOID:
		return any(boost::lexical_cast<std::string>(dbData.value));
	case TIMESTAMPOID:{
		std::string format("%Y-%m-%d %H:%M:%S%F%Q");

		std::unique_ptr<date_input_facet> date_input( new date_input_facet(format));
		std::unique_ptr<time_input_facet> time_input( new time_input_facet(format));


		std::stringstream stream(dbData.value.data());
		stream.imbue(std::locale(stream.getloc(), date_input.release()));
		stream.imbue(std::locale(stream.getloc(), time_input.release()));

		ptime timeStamp;
		stream >> timeStamp;
		return any(timeStamp);
		}
	default:
		throw DBExceptionInvalidDataType(dbData.type);
	}
}

char* DBDataConverter::getStringValue(const any value) {
	std::stringstream stream;

	if (value.type() == typeid(int32_t)) {
		stream << any_cast<int32_t>(value);
	} else if (value.type() == typeid(int64_t)) {
		stream << any_cast<int64_t>(value);
	} else if (value.type() == typeid(double)) {
		stream << any_cast<double>(value);
	} else if (value.type() == typeid(double)) {
		stream << any_cast<double>(value);
	} else if (value.type() == typeid(bool)) {
		stream << (any_cast<bool>(value)  ? "t" : "f");
	} else if (value.type() == typeid(std::string)) {
		stream << any_cast<std::string>(value);
    } else if (value.type() == typeid(std::string_view)) {
        stream << any_cast<std::string_view>(value);
    } else if (value.type() == typeid(ptime)){
        stream << to_iso_string(any_cast<ptime>(value));
    } else if (value.type() == typeid(boost::any)){
        boost::any a = any_cast<boost::any>(value);
        BOOST_LOG_TRIVIAL(error) << "boost::any Unsupported type: " << a.type().name();
	} else {
        BOOST_LOG_TRIVIAL(error) << "Unsupported type: " << value.type().name();
    }
	char * res = strdup(stream.str().c_str());
    return res;
}

} /* namespace zigbee */
