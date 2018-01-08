/*
 * ClusterTypeFactory.cpp
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include "ClusterTypeFactory.h"
#include "clusterTypes/BasicCluster.h"
#include "clusterTypes/IdentifyCluster.h"
#include "clusterTypes/NullCluster.h"
#include "clusterTypes/PowerConfigurationCluster.h"
#include "clusterTypes/DeviceTemperatureConfiguration.h"
#include "clusterTypes/GroupsCluster.h"
#include "clusterTypes/ScenesCluster.h"
#include "clusterTypes/OnOffCluster.h"
#include "clusterTypes/LevelControlCluster.h"
#include "clusterTypes/IlluminanceMeasurementCluster.h"
#include "clusterTypes/IlluminanceLevelSensingCluster.h"
#include "clusterTypes/TemperatureMeasurementCluster.h"
#include "clusterTypes/PressureMeasurementCluster.h"
#include "clusterTypes/FlowMeasurementCluster.h"
#include "clusterTypes/RelativeHumidityMeasurementCluster.h"
#include "clusterTypes/OccupancySensingCluster.h"
#include "clusterTypes/MeteringCluster.h"
#include "clusterTypes/ElectricalMeasurementCluster.h"
#include "clusterTypes/TestCluster.h"

namespace zigbee {

using namespace std;

	unique_ptr<Cluster> ClusterTypeFactory::createCluster(ClusterID clusterId, ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) {

	std::cout << "CLUSTERD ID: " << clusterId << std::endl;

	switch (clusterId.getId()) {
	case BASIC_CLUSTER:
		return make_unique<BasicCluster>(zigbeeDevice, endpoint, networkAddress);
	case POWER_CONFIGURATION_CLUSTER:
			return make_unique<PowerConfigurationCluster>(zigbeeDevice, endpoint, networkAddress);
	case DEVICE_TEMPERATURE_CONFIG_CLUSTER:
			return make_unique<DeviceTemperatureConfiguration>(zigbeeDevice, endpoint, networkAddress);
	case IDENTIFY_CLUSTER:
		return make_unique<IdentifyCluster>(zigbeeDevice, endpoint, networkAddress);
	case GROUPS_CLUSTER:
			return make_unique<GroupsCluster>(zigbeeDevice, endpoint, networkAddress);
	case SCENE_CLUSTER:
			return make_unique<ScenesCluster>(zigbeeDevice, endpoint, networkAddress);
	case ON_OFF_CLUSTER:
			return make_unique<On_Off_Cluster>(zigbeeDevice, endpoint, networkAddress);
	case LEVEL_CONTROL:
			return make_unique<LevelControlCluster>(zigbeeDevice, endpoint, networkAddress);
	case ILLUMINANCE_MEASUREMENT:
			return make_unique<IlluminanceMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case ILLUMINANCE_LEVEL_SENSING:
			return make_unique<IlluminanceLevelSensingCluster>(zigbeeDevice, endpoint, networkAddress);
	case TEMPERATURE_MEASUREMENT:
			return make_unique<TemperatureMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case PRESSURE_MEASUREMENT:
			return make_unique<PressureMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case FLOW_MEASUREMENT:
			return make_unique<FlowMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case RELATIVE_HUMIDITY_MEASUREMENT:
			return make_unique<RelativeHumidityMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case OCCUPANCY_SENSING:
			return make_unique<OccupancySensingCluster>(zigbeeDevice, endpoint, networkAddress);
	case METERING:
			return make_unique<MeteringCluster>(zigbeeDevice, endpoint, networkAddress);
	case ELECTRICITY_MEASURE:
			return make_unique<ElectricalMeasurementCluster>(zigbeeDevice, endpoint, networkAddress);
	case TEST_CLUSTER:
			return make_unique<TestCluster>(zigbeeDevice, endpoint, networkAddress);
	default:
		return make_unique<NullCluster>(zigbeeDevice, endpoint, networkAddress, clusterId);
	}

}

std::unique_ptr<Cluster> ClusterTypeFactory::getCluster(ClusterID clusterId, ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) {
	return createCluster(clusterId, zigbeeDevice, endpoint, networkAddress) ;
}

} /* namespace zigbee */

