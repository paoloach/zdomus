/*
 * DBTable.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBTABLE_H_
#define SRC_DATABASE_DBTABLE_H_

#include <boost/any.hpp>
#include <memory>
#include <string>
#include <libpq-fe.h>

#include "DBRow.h"

namespace zigbee {

    class DBTable {
    public:
        DBTable();

        DBTable(const std::string &tableName, PGconn *conn);

        virtual ~DBTable()=default;

    public:
        virtual PGresult * find(const std::string &query);

        virtual void insert(DBRow *dbRow);

    private:
        std::string tableName;
        PGconn *conn;
        uint currentIndex;

        void checkTableName(const std::string &tableName);
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBTABLE_H_ */
