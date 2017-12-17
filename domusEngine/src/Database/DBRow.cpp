/*
 * DBRow.cpp
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include "DBRow.h"

using std::any;

namespace zigbee {
    any DBRow::getValue(const std::string_view &fieldName) {
        if (values.count(fieldName)) {
            return values[fieldName];
        }
        BOOST_LOG_TRIVIAL(error) << "Unable to find field: " << fieldName;
        return any {};
    }

    std::vector<std::string_view> DBRow::getFieldsName() const {
        std::vector<std::string_view> fieldsName;
        for (auto value : values) {
            fieldsName.push_back(value.first);
        }
        return fieldsName;
    }


    std::vector<any> DBRow::getFieldsValue() const {
        std::vector<any> fieldsValue;
        for (auto value : values) {
            fieldsValue.push_back(value.second);
        }
        return fieldsValue;
    }

} /* namespace zigbee */
