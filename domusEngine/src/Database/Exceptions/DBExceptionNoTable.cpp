/*
 * DBExceptionNoTable.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include "DBExceptionNoTable.h"

namespace zigbee {

    DBExceptionNoTable::DBExceptionNoTable(const std::string &tableName) {
        message = "Unable to find database table " + tableName;
    }
} /* namespace zigbee */
