/*
 * ComandFactory.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include "ComandFactory.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include "Comands.h"
#include "CmdGetUpdate.h"
#include "CmdSendCmd.h"
#include "CmdNull.h"
#include "CmdUpdateAttribute.h"
#include "CmdRequestAttribute.h"
#include "jsonFields.h"

namespace zigbee {

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using boost::property_tree::ptree;
using boost::property_tree::ptree_bad_data;
using boost::property_tree::ptree_bad_path;
using namespace boost::property_tree::json_parser;

Comand_P ComandFactory::createComand(const std::string & code, ZDevices & zDevices, ZigbeeDevice & zigbeeDevice, AttributeDataContainer & attributeDataContainer) {
	if (code == UPDATE_CMD) {
		shared_ptr<CmdGetUpdate> cmd = make_shared<CmdGetUpdate>(zDevices);
		return dynamic_pointer_cast<Comand>(cmd);
	} else if (code == UPDATE_ATTRIBUTE_CMD) {
		shared_ptr<CmdUpdateAttribute> cmd = make_shared<CmdUpdateAttribute>(attributeDataContainer);
		return dynamic_pointer_cast<Comand>(cmd);
	} else if (code == REQUEST_ATTRIBUTE_CMD) {
		shared_ptr<CmdRequestAttribute> cmd = make_shared<CmdRequestAttribute>(zigbeeDevice);
		return dynamic_pointer_cast<Comand>(cmd);
	} else if (code == SEND_COMMAND_CMD) {
		shared_ptr<CmdSendCmd> cmd = make_shared<CmdSendCmd>(zigbeeDevice);
		return dynamic_pointer_cast<Comand>(cmd);
	} else {
		return dynamic_pointer_cast<Comand>(make_shared<CmdNull>());
	}
}

std::vector<Comand_P> ComandFactory::createComands(const std::string& code, ZDevices& zDevices, ZigbeeDevice& zigbeeDevice, AttributeDataContainer& attributeDataContainer) {
	std::stringstream inStream(code);
	ptree properties { };
	std::vector<Comand_P> comands { };

	try {
		read_json(inStream, properties);
	} catch (json_parser_error & error) {
		std::cerr << "ERROR: " << error.message() << std::endl;
	}

	try {
		uint64_t tokenId = properties.get<uint64_t>(UPDATE_CMD);
		shared_ptr<CmdGetUpdate> cmd = make_shared<CmdGetUpdate>(zDevices);
		cmd->setTokenId(tokenId);
		comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));
	} catch (ptree_bad_data & badData) {
		std::cerr << "ERROR converting the argument of " << UPDATE_CMD << " : " << badData.what() << std::endl;
	} catch (ptree_bad_path & badData) {
		// no update command
	}

	try {
		uint64_t tokenId = properties.get<uint64_t>(UPDATE_ATTRIBUTE_CMD);
		shared_ptr<CmdUpdateAttribute> cmd = make_shared<CmdUpdateAttribute>(attributeDataContainer, tokenId);
		comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));
	} catch (ptree_bad_data & badData) {
		std::cerr << "ERROR converting the argument of " << UPDATE_ATTRIBUTE_CMD << " : " << badData.what() << std::endl;
	} catch (ptree_bad_path & badData) {
		// no update command
	}

	try {
		auto requestes = properties.equal_range(PROPERTIES_REQUEST_NAME);
		for (;requestes.first != requestes.second; requestes.first++){
			shared_ptr<CmdRequestAttribute> cmd = make_shared<CmdRequestAttribute>(zigbeeDevice, (*(requestes.first)).second);
			comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));
		}
	} catch (ptree_bad_data & badData) {
		std::cerr << "ERROR converting the argument of " << UPDATE_ATTRIBUTE_CMD << " : " << badData.what() << std::endl;
	} catch (ptree_bad_path & badData) {
		// no update command
	}

	try {
//		for (auto a: properties){
//			std::cout << a.first << std::endl;
//			if (a.first == SEND_CMD_NAME){
//				std::cout << "Found " << std::endl;
//				shared_ptr<CmdSendCmd> cmd = make_shared<CmdSendCmd>(zigbeeDevice, a.second);
//				comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));
//			} else {
//				std::cout << a.first << " is different from " << SEND_CMD_NAME << std::endl;
//			}
//		}
//		ptree sendCmdProperties = properties.get_child(SEND_CMD_NAME);
//		shared_ptr<CmdSendCmd> cmd = make_shared<CmdSendCmd>(zigbeeDevice, sendCmdProperties);
//		comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));

		auto requestes = properties.equal_range(SEND_COMMAND_CMD);
//
		for (;requestes.first != requestes.second; requestes.first++){
			std::cout << "------------------------ found send_cmd request" << std::endl;
		shared_ptr<CmdSendCmd> cmd = make_shared<CmdSendCmd>(zigbeeDevice, (*(requestes.first)).second);
			comands.push_back(std::dynamic_pointer_cast<Comand>(cmd));
		}
	} catch (ptree_bad_data & badData) {
		std::cerr << "ERROR converting the argument of " << UPDATE_ATTRIBUTE_CMD << " : " << badData.what() << std::endl;
	} catch (ptree_bad_path & badData) {
		// no send cmd command
	}

	return comands;
}
} /* namespace zigbee */
