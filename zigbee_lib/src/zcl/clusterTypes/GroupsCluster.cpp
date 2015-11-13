/*
 * GroupsCluster.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include "GroupsCluster.h"

namespace zigbee {

using std::make_shared;
static std::vector<Cluster::AttributeDef> attributesDef { Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0, "Name Support", true), };

GroupsCluster::GroupsCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);



	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "send add group: data is " << std::endl;}, 0, "Add group",
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("Group Name"));


	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "View group " << std::endl;}, 1, "View group",
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"));
	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "Get Group Memebership " << std::endl;}, 2, "Get Group Memebership",
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Group Count"),
			make_shared<ClusterCmdListParams<ZCLTypeDataType::ZCLTypeArray>>("Group List"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "send remove group " << std::endl;}, 3, "Remove group",
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "send remove All Groups " << std::endl;}, 4, "Remove All Groups");

	_commandsDef.emplace_back([&](std::vector<uint8_t> && ) { std::cout << "send group if identifying" << std::endl;}, 5, "Send group if identifying",
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("Group Name"));

}

ClusterID GroupsCluster::getId() {
	return GroupsClusterID;
}

std::string GroupsCluster::getClusterName() {
	return "Groups";
}



} /* namespace zigbee */
