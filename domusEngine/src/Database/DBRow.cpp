/*
 * DBRow.cpp
 *
 *  Created on: 21/gen/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include "DBRow.h"

namespace zigbee {

DBRow::DBRow() {
}

DBRow::~DBRow() {
}

boost::any DBRow::getValue(const std::string& fieldName) {
	if (values.count(fieldName)) {
		return values[fieldName];
	}
	return boost::any { };
}

void DBRow::setValue(const std::string& fieldName, const boost::any& any) {
	values[fieldName] = any;
}

std::vector<std::string> DBRow::getFieldsName() const {
	std::vector<std::string> fieldsName;
	for (auto value : values) {
		fieldsName.push_back(value.first);
	}
	return fieldsName;
}


std::vector<boost::any> DBRow::getFieldsValue() const {
	std::vector<boost::any> fieldsValue;
	for (auto value : values) {
		fieldsValue.push_back( value.second);
	}
	return fieldsValue;
}

} /* namespace zigbee */
