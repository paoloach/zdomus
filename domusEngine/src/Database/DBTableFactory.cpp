/*
 * DBTableFactory.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "DBTableFactory.h"
#include "DBTable.h"
#include "Exceptions/DBExceptionNoServer.h"

namespace zigbee {

    static constexpr const char *server = "localhost:5432";
    static constexpr const char *database = "domusEngine";
    static constexpr const char *user = "DomusEngine";
    static constexpr const char *password = "DomusEngine";


    DBTable *DBTableFactory::getTable(const std::string &tableName) const {
        return new DBTable(tableName, conn);
    }

    DBTableFactory::DBTableFactory() {
        std::stringstream connectionStream;

        connectionStream << "hostaddr = '127.0.0.1' dbname = " << database << " user = " << user << " password = " << password;
        conn = PQconnectdb(connectionStream.str().c_str());

        if (conn == nullptr) {
            throw DBExceptionNoServer(server, database);
        }

        if (PQstatus(conn) != CONNECTION_OK) {
            throw DBExceptionNoServer(server, database, PQerrorMessage(conn));
        }
    }

} /* namespace zigbee */
