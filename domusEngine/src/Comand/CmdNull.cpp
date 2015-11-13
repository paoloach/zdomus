/*
 * CmdNull.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include "CmdNull.h"

namespace zigbee {

CmdNull::CmdNull() {
}

CmdNull::~CmdNull() {
}

bool CmdNull::parseData(const std::string &) {
	return true;
}

void CmdNull::execute() {

}

void CmdNull::getResponse(boost::property_tree::ptree & ) {
}

} /* namespace zigbee */
