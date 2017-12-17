//
// Created by paolo on 17/12/17.
//

#include "ResultSet.h"
#include "DBDataConverter.h"
#include "../json/json/json.h"

using namespace Json;

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

    std::string ResultSet::stringify() {
        Value root(arrayValue);
        int nTuples = numberOfRow();
        int nRow = numberOfField();
        for(int tuple = 0; tuple < nTuples; tuple++){
            Value object(objectValue);
            for(int row=0; row < nRow; row++){
                auto colName = columnName(row);
                auto dbData = DBDataConverter::DBData(this, tuple, row);
                std::any value = DBDataConverter::getAnyValue(dbData);
                object[colName] =  DBDataConverter::getStringValue(value);
            }
            root.append(object);
        }
        std::stringstream stream;
        stream << root << "\r\n";
        return stream.str();
    }
}
