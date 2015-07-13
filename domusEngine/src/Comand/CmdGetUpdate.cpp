/*
 * CmdGetUpdate.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <algorithm>
#include "CmdGetUpdate.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {

const std::string CmdGetUpdate::INVALID_TOKEN_MSG("INVALID TOKEN");

CmdGetUpdate::CmdGetUpdate(ZDevices & zDevices_) :
		zDevices(zDevices_), token(0) {
	badToken = false;
}

CmdGetUpdate::~CmdGetUpdate() {
}

bool CmdGetUpdate::parseData(const std::string &line) {
	strToken = line;
	try {
		token = boost::lexical_cast<uint64_t>(line);
	} catch (const boost::bad_lexical_cast &) {
		badToken = true;
	}
	return true;
}

void CmdGetUpdate::execute() {
}

void CmdGetUpdate::getResponse(boost::property_tree::ptree & result) {
	boost::property_tree::ptree differences = zDevices.getDifferences(token);
	std::copy(differences.begin(), differences.end(), std::back_inserter(result));
}

void CmdGetUpdate::setTokenId(uint64_t token_) {
	this->token = token_;
}

} /* namespace zigbee */
