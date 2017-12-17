//
// Created by paolo on 17/12/17.
//

#ifndef DOMUS_ENGINE_RESULTSET_H
#define DOMUS_ENGINE_RESULTSET_H

#include <libpq-fe.h>
#include <any>
#include <string_view>

namespace zigbee {
    class ResultSet {
    public:
        enum FORMAT_CODE {
            BINARY, TEXT
        };
    public:
        ResultSet(pg_result *pgResult) : resultSet{pgResult}, currentIndex{0} {}

        std::any getValue(std::string_view colNam);
        std::string stringify();

        int numberOfRow() { return PQntuples(resultSet); }

        int numberOfField() { return PQnfields(resultSet); }

        std::string_view columnName(int index) {
            return PQfname(resultSet, index);
        }

        bool fieldIsNull(int rowIndex, int colIndex) { return PQgetisnull(resultSet, rowIndex, colIndex) == 1; }

        Oid getFieldType(int colIndex) {
            return PQftype(resultSet, colIndex);
        }

        int getModifier(int colIndex) { return PQfmod(resultSet, colIndex); }

        int getFieldLength(int colIndex, int rowIndex) { return PQgetlength(resultSet, rowIndex, colIndex); }

        std::string_view getRawValue(int colIndex, int rowIndex) {
            int fieldLength = PQgetlength(resultSet, rowIndex, colIndex);
            char *data = PQgetvalue(resultSet, rowIndex, colIndex);
            return std::string_view(data, fieldLength);
        };

        FORMAT_CODE getFormatCode(int colIndex) { return PQfformat(resultSet, colIndex) == 0 ? TEXT : BINARY; }

    private:
        pg_result *resultSet;
        int currentIndex;
    };
}


#endif //DOMUS_ENGINE_RESULTSET_H
