/*
 * CmdRequestAttribute.cpp
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "jsonFields.h"

#include "CmdRequestAttribute.h"

namespace zigbee {

using boost::property_tree::ptree;
using namespace boost::property_tree::json_parser;

CmdRequestAttribute::CmdRequestAttribute(ZigbeeDevice & zigbeeDevice_) :
		 zigbeeDevice(zigbeeDevice_),attributeId{0} {
}

CmdRequestAttribute::CmdRequestAttribute(ZigbeeDevice& zigbeeDevice_, boost::property_tree::ptree& request) :
		zigbeeDevice(zigbeeDevice_) {
	init(request);
}

CmdRequestAttribute::~CmdRequestAttribute() {
}

bool CmdRequestAttribute::parseData(const std::string& line) {
	std::stringstream stream { line };
	ptree properties { };

	try {
		read_json(stream, properties);

		init(properties);
		response = "OK";
	} catch (boost::property_tree::ptree_error & error) {
		std::cerr << error.what() << std::endl;
		response = error.what();
	}
	return true;
}

void CmdRequestAttribute::execute() {
	std::cout << "Request attribute [" << nwkAddress << ", " << endpoint << ", " << cluster << ", " << attributeId << "]" << std::endl;
	zigbeeDevice.requestAttribute(AttributeKey{nwkAddress, endpoint, cluster, attributeId});
}

void CmdRequestAttribute::getResponse(boost::property_tree::ptree &) {
//	ptree property { };
//	std::stringstream responseStream { };
//	property.put(RESPONSE_NAME, response);
//	write_json(responseStream, property, false);

//	return responseStream.str();
}

void CmdRequestAttribute::init(boost::property_tree::ptree& request) {
	nwkAddress = request.get<NwkAddr>(SHORT_ADDR_NAME);
	endpoint = request.get<EndpointID>(ENDPOINT_ID_NAME);
	cluster = request.get<ClusterID>(CLUSTER_ID_NAME);
	attributeId = request.get<int>(ATTR_ID_NAME);
}

} /* namespace zigbee */

