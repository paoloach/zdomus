/*
 * DBTableFactory.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBTABLEFACTORY_H_
#define SRC_DATABASE_DBTABLEFACTORY_H_

#include <string>
#include <libpq-fe.h>
namespace zigbee {

    class DBTable;

    class DBTableFactory {
    public:
        DBTableFactory();
        virtual ~DBTableFactory()=default;

    public:
        virtual DBTable *getTable(const std::string &tableName) const;
    private:
        PGconn *conn;
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBTABLEFACTORY_H_ */
