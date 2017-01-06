/*
 * DBTable.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <iostream>
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

    std::shared_ptr<DBRow> DBTable::makeDBRow(PGresult *resultSet, uint index) {
        std::shared_ptr<DBRow> dbRow = std::make_shared<DBRow>();

        int fieldCount = PQnfields(resultSet);

        for (int colIndex = 0; colIndex < fieldCount; colIndex++) {
            std::string fieldName = PQfname(resultSet, colIndex);
            if (PQgetisnull(resultSet, index, colIndex) == 0) {
                DBDataConverter::DBData dbData(resultSet, index, colIndex);
                boost::any value = DBDataConverter::getAnyValue(dbData);
                dbRow->setValue(fieldName, value);
            } else {
                dbRow->setValue(fieldName, boost::any());
            }
        }
        return dbRow;

    }

    void DBTable::insert(DBRow *dbRow) {
        std::stringstream insertStream;
        std::vector<std::string> paramName = dbRow->getFieldsName();
        std::vector<boost::any> paramAnyValues = dbRow->getFieldsValue();

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

    void DBTable::checkTableName(const std::string &tableName) {

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

    DBTable::DBTable(const std::string &tableName, PGconn *conn) : tableName(tableName), conn(conn) {
        resultSet = nullptr;

        checkTableName(tableName);
        currentIndex = 0;
    }

    DBTable::DBTable() {
        conn = nullptr;
        resultSet = nullptr;
        currentIndex = 0;
    }

    DBTable::~DBTable() {
        if (resultSet != nullptr) {
            PQclear(resultSet);
        }
    }

    std::shared_ptr<DBRow> DBTable::nextRow() {
        uint maxResult = PQntuples(resultSet);
        if (currentIndex == maxResult - 1) {
            return std::shared_ptr<DBRow>();
        } else {
            currentIndex++;
            return makeDBRow(resultSet, currentIndex);
        }
    }

    std::shared_ptr<DBRow> DBTable::previousRow() {
        if (currentIndex == 0) {
            return std::shared_ptr<DBRow>();
        } else {
            currentIndex--;
            return makeDBRow(resultSet, currentIndex);
        }
    }

    std::shared_ptr<DBRow> DBTable::find(const std::string &filter) {
        std::string query = "select * from public.\"" + tableName + "\"";
        if (!filter.empty()) {
            query += " where " + filter;
        }
        query += ";";
        if (resultSet != nullptr) {
            PQclear(resultSet);
        }
        resultSet = PQexecParams(conn, query.c_str(), 0, nullptr, nullptr, nullptr, nullptr, 0);
        ExecStatusType status = PQresultStatus(resultSet);
        switch (status) {
            case PGRES_COMMAND_OK:
            case PGRES_EMPTY_QUERY:
                return std::unique_ptr<DBRow>();
            case PGRES_TUPLES_OK:
                currentIndex = 0;
                return makeDBRow(resultSet, 0);
            default:
                throw DBExceptionQueryError(query, tableName, PQresultErrorMessage(resultSet));
        }
    }

} /* namespace zigbee */
