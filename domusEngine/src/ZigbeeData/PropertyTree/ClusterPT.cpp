/*
 * ClusterPT.cpp
 *
 *  Created on: 28/apr/2015
 *      Author: Paolo Achdjian
 */
#include <boost/lexical_cast.hpp>
#include "ClusterPT.h"

namespace zigbee {

using boost::property_tree::ptree;

ClusterPT::ClusterPT(const Cluster* cluster) noexcept {
	ptree attributes;
	ptree commands;

	add("cluster id", cluster->getId());
	add("cluster name", cluster->getClusterName());
	for (auto attribute : cluster->getAttributes()) {
		attributes.add(std::to_string(attribute.id), attribute.name);
	}
	push_back( { "attributes", attributes });
	for (auto & command : cluster->getCommands()) {
		commands.add(std::to_string(command.cmdId), command.name);
	}
	push_back( { "commands", commands });

}


} /* namespace zigbee */
