/*
 * CmdSendCmd.cpp
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <iostream>

#include "CmdSendCmd.h"
#include "jsonFields.h"
#include "../IO/ProperyTreeUtils.h"

namespace zigbee {

using boost::property_tree::ptree;
using namespace boost::property_tree::json_parser;

CmdSendCmd::CmdSendCmd(ZigbeeDevice & zigbeeDevice) :cmdId{0},
		zigbeeDevice(zigbeeDevice) {
}

CmdSendCmd::CmdSendCmd(ZigbeeDevice& zigbeeDevice, boost::property_tree::ptree& request) :
				zigbeeDevice(zigbeeDevice) {
	nwkAddress = request.get<NwkAddr>(SHORT_ADDR_NAME);
	endpoint = request.get<EndpointID>(ENDPOINT_ID_NAME);
	cluster = request.get<ClusterID>(CLUSTER_ID_NAME);
	cmdId = request.get<int>(COMMAND_ID_NAME);
}

CmdSendCmd::~CmdSendCmd() {
}

bool CmdSendCmd::parseData(const std::string& line) {
	std::stringstream stream { line };
	ptree properties { };

	try {
		read_json(stream, properties);

		nwkAddress = properties.get<NwkAddr>(SHORT_ADDR_NAME);
		endpoint = properties.get<EndpointID>(ENDPOINT_ID_NAME);
		cluster = properties.get<ClusterID>(CLUSTER_ID_NAME);
		cmdId = properties.get<int>(COMMAND_ID_NAME);
		ProperyTreeUtils::read(properties, data);
		response = "OK";
	} catch (boost::property_tree::ptree_error & error) {
		std::cerr << error.what() << std::endl;
		response = error.what();
	}
	return true;
}

void CmdSendCmd::execute() {
	zigbeeDevice.sendCmd(nwkAddress, endpoint, cluster, cmdId, data);
}

void CmdSendCmd::getResponse(boost::property_tree::ptree & ) {
//	ptree property { };
//	std::stringstream responseStream { };
//	property.put(RESPONSE_NAME, response);
//	write_json(responseStream, property);

}

} /* namespace zigbee */

