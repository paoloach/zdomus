//
// Created by paolo on 17/12/17.
//

#include "ResultSet.h"
#include "DBDataConverter.h"

namespace zigbee {
    std::any ResultSet::getValue(std::string_view colNam) {
        auto colNum = PQfnumber(resultSet, colNam.data());
        if (colNum >= 0) {
            auto dbData = DBDataConverter::DBData(this, currentIndex,colNum);
            return DBDataConverter::getAnyValue(dbData);
        } else {
            return std::any();
        }
    }
}
