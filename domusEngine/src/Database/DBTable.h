/*
 * DBTable.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBTABLE_H_
#define SRC_DATABASE_DBTABLE_H_

#include <memory>
#include <string>
#include <libpq-fe.h>

#include "DBRow.h"
#include "ResultSet.h"

namespace zigbee {

    class DBTable {
    public:
        DBTable();

        DBTable(const std::string_view tableName, PGconn *conn);

        virtual ~DBTable()=default;

    public:
        virtual ResultSet find(const std::string &query);

        virtual void insert(DBRow *dbRow);

    private:
        std::string tableName;
        PGconn *conn;

        void checkTableName(const std::string &&tableName);
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBTABLE_H_ */
