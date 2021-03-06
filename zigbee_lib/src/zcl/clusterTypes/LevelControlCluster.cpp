/*
 * LevelControlCluster.cpp
 *
 *  Created on: 07/nov/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>

#include "LevelControlCluster.h"

namespace zigbee {

using std::make_unique;

static std::vector<ClusterImpl::AttributeDef> attributesDef {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0, "Current Level", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 1,"Remaining Time", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 2, "On/Off Transiction Time"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 3, "On Level") };

LevelControlCluster::LevelControlCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);

	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 0, std::move(data));}, 0, "Move to Level",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Level"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Transition time (tenths of sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 1, std::move(data));}, 1, "Move",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Move mode"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Rate (unit x sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 2, std::move(data));}, 2, "Step",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Move Mode"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Step Size"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Transition time (tenths of sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 3, std::move(data));}, 3, "Stop");
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 4, std::move(data));}, 4, "Move to Level (On/Off)",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Level"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Transition time (tenths of sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 5, std::move(data));}, 5, "Move (On/Off)",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Move mode"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Rate (unit x sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 6, std::move(data));}, 6, "Step (On/Off)",
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Move Mode"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt8>>("Step Size"),
			std::make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("Transition time (tenths of sec)"));
	_commandsDef.emplace_back([=](std::vector<uint8_t> && data ) { zigbeeDevice->sendCmd(networkAddress, endpoint, LevelControClusterID, 7, std::move(data));}, 7, "Stop (On/Off)");
	// @formatter:on

}

ClusterID LevelControlCluster::getId()  const {
	return LevelControClusterID;
}

std::string LevelControlCluster::getClusterName()  const {
	return "Level Control";
}


} /* namespace zigbee */
