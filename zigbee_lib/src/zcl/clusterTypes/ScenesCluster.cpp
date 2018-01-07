/*
 * ScenesCluster.cpp
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>


#include "ScenesCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef = {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0, "Scene Count", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 1, "Current Scene", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "Current Group", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeBool, 3, "Scene Valid", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 4, "Name Supported", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeIEEEaddress, 5, "Last Configured By", true)
		};

ScenesCluster::ScenesCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {

	createAttributes(attributesDef);


	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send add scene: data is " << std::endl;}, 0, "Add Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Scene ID"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Transition Time"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("Scene Name"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("Extension Field Set"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send view Scene: data is " << std::endl;}, 1, "View Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Scene ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send Remove Scene: data is " << std::endl;}, 2, "Remove Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
									std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Scene ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send Remove All Scene: data is " << std::endl;}, 3, "Remove All Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send Store Scene: data is " << std::endl;}, 4, "Store Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Scene ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send Store Scene: data is " << std::endl;}, 5, "Recall Scene",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Scene ID"));

	_commandsDef.emplace_back([&](std::vector<uint8_t> && data ) { std::cout << "send Get Scene Membership: data is " << std::endl;}, 6, "Get Scene Membership",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group ID"));

}

ClusterID ScenesCluster::getId()  const {
	return SceneClusterID;
}

std::string ScenesCluster::getClusterName() const {
	return "Scenes";
}

} /* namespace zigbee */
