/*
 * ResponseCreator.cpp
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ResponseCreator.h"

namespace zigbee {

std::string ResponseCreator::generateResponse(std::vector<Comand_P>& comands) {
	std::stringstream stream {};
	boost::property_tree::ptree properties {};

	for(Comand_P &  comand: comands){
		comand->execute();
		comand->getResponse(properties);
	}
	boost::property_tree::json_parser::write_json(stream, properties,false);
	return stream.str();
}

} /* namespace zigbee */

