/*
 * DeviceTemperatureConfiguration.h
 *
 *  Created on: 12/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef DEVICETEMPERATURECONFIGURATION_H_
#define DEVICETEMPERATURECONFIGURATION_H_

#include <string>
#include <memory>
#include "../Cluster.h"
#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {

class DeviceTemperatureConfiguration : public Cluster{
public:
	DeviceTemperatureConfiguration(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
public:
	ClusterID getId() const override;
	std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* DEVICETEMPERATURECONFIGURATION_H_ */
