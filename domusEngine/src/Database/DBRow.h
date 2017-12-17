/*
 * DBRow.h
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_DBROW_H_
#define SRC_DATABASE_DBROW_H_

#include <boost/any.hpp>
#include <map>
#include <string.h>
#include <any>
#include <string_view>
#include <vector>

namespace zigbee {

    class DBRow {
    public:
        virtual ~DBRow() = default;

    public:
        std::any getValue(const std::string_view &fieldName);

        void setValue(const std::string_view &fieldName, const std::any &any) {values[fieldName] = any;}

        std::vector<std::string_view> getFieldsName() const;

        std::vector<std::any> getFieldsValue() const;

    private:
        std::map<std::string_view, std::any> values;
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBROW_H_ */
