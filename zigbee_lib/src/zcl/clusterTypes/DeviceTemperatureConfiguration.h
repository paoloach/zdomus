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
	DeviceTemperatureConfiguration(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
public:
	virtual ClusterID getId() const override;
	virtual std::string getClusterName() const override;
};

} /* namespace zigbee */

#endif /* DEVICETEMPERATURECONFIGURATION_H_ */
