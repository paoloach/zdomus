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
#include <vector>

namespace zigbee {

    class DBRow {
    public:
        virtual ~DBRow() = default;

    public:
        boost::any getValue(const std::string &fieldName);

        void setValue(const std::string &fieldName, const boost::any &any);

        std::vector<std::string> getFieldsName() const;

        std::vector<boost::any> getFieldsValue() const;

    private:
        std::map<std::string, boost::any> values;
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_DBROW_H_ */
