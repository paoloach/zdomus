/*
 * DBTable.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <boost/log/trivial.hpp>
#include <boost/spirit/include/karma.hpp>
#include "DBTable.h"
#include "DBDataConverter.h"
#include "Exceptions/DBExceptionNoServer.h"
#include "Exceptions/DBExceptionNoTable.h"
#include "Exceptions/DBExceptionQueryError.h"

namespace zigbee {

    using std::stringstream;
    using std::shared_ptr;
    using namespace boost::spirit::karma;

    void DBTable::insert(DBRow *dbRow) {
        std::stringstream insertStream;
        auto paramName = dbRow->getFieldsName();
        auto paramAnyValues = dbRow->getFieldsValue();

        insertStream << "INSERT INTO public.\"" << tableName << "\" (";
        insertStream << format(string % ',', paramName) << ") VALUES (";
        for (uint i = 1; i < paramName.size(); i++) {
            insertStream << "$" << i << ",";
        }
        insertStream << "$" << paramName.size() << ")";

        char **paramsValue = new char *[paramName.size()];
        for (uint i = 0; i < paramAnyValues.size(); i++) {
            paramsValue[i] = DBDataConverter::getStringValue(paramAnyValues[i]);
        }


        PGresult *insertResult = PQexecParams(conn, insertStream.str().c_str(), paramName.size(), nullptr, paramsValue, nullptr, nullptr, 0);
        for (uint i = 0; i < paramAnyValues.size(); i++) {
            free(paramsValue[i]);
        }

        delete[] paramsValue;

        ExecStatusType status = PQresultStatus(insertResult);
        if (status != PGRES_COMMAND_OK) {
            PQclear(insertResult);
            throw DBExceptionQueryError(insertStream.str(), tableName, PQresultErrorMessage(insertResult));
        }
        PQclear(insertResult);

    }

    void DBTable::checkTableName(const std::string &&tableName) {

        std::string checkTableStream;
        checkTableStream = "SELECT EXISTS (SELECT 1 FROM   pg_catalog.pg_class c  JOIN   pg_catalog.pg_namespace n ON n.oid = c.relnamespace  ";
        checkTableStream += " WHERE  n.nspname = 'public'   AND    c.relname = '" + tableName + "' AND    c.relkind = 'r');";

        PGresult *result = PQexecParams(conn, checkTableStream.c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
        ExecStatusType status = PQresultStatus(result);
        if (status != PGRES_TUPLES_OK) {
            throw DBExceptionNoServer(PQresultErrorMessage(result));
        }
        char *field = PQgetvalue(result, 0, 0);
        bool tableExist = *(bool *) (field);
        PQclear(result);
        if (!tableExist) {
            throw DBExceptionNoTable(tableName);
        }
    }

    DBTable::DBTable(const std::string_view tableName, PGconn *conn) : tableName(tableName), conn(conn) {
        checkTableName(std::string(tableName));
    }

    DBTable::DBTable() {
        conn = nullptr;
    }

    ResultSet  DBTable::find(const std::string &filter) {
        std::string query = "select * from public.\"" + tableName + "\"";
        if (!filter.empty()) {
            query += " where " + filter;
        }
        query += ";";
        BOOST_LOG_TRIVIAL(info) << "Search query: " << query;
        PGresult * resultSet = PQexecParams(conn, query.c_str(), 0, nullptr, nullptr, nullptr, nullptr, 0);
        ExecStatusType status = PQresultStatus(resultSet);
        switch (status) {
            case PGRES_COMMAND_OK:
            case PGRES_EMPTY_QUERY:
                return ResultSet(resultSet);
            case PGRES_TUPLES_OK:
                return ResultSet(resultSet);
            default:
                throw DBExceptionQueryError(query, tableName, PQresultErrorMessage(resultSet));
        }
    }

} /* namespace zigbee */
