/*
 * CmdUpdateAttribute.cpp
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

#include "CmdUpdateAttribute.h"
#include "../IO/AttributeDataContainer.h"

namespace zigbee {

const std::string CmdUpdateAttribute::INVALID_TOKEN_MSG("INVALID TOKEN: ");

CmdUpdateAttribute::CmdUpdateAttribute(AttributeDataContainer & attributes) :
		attributes(attributes), token(0) {
	badToken = false;
}

CmdUpdateAttribute::CmdUpdateAttribute(AttributeDataContainer& attributes, uint64_t token) :
		attributes(attributes), token(token) {
	badToken = false;
}

CmdUpdateAttribute::~CmdUpdateAttribute() {
}

bool CmdUpdateAttribute::parseData(const std::string& line) {
	strToken = line;
	try {
		token = boost::lexical_cast<uint64_t>(line);
	} catch (const boost::bad_lexical_cast &) {
		badToken = true;
	}
	return true;
}

void CmdUpdateAttribute::execute() {
}

void CmdUpdateAttribute::getResponse(boost::property_tree::ptree & result) {
		boost::property_tree::ptree newAttributes = attributes.get(token);
		std::copy(newAttributes.begin(), newAttributes.end(), std::back_inserter(result));
}

} /* namespace zigbee */
