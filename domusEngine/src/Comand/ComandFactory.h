/*
 * ComandFactory.h
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_COMANDFACTORY_H_
#define SRC_COMAND_COMANDFACTORY_H_

#include <memory>
#include <vector>
#include <zigbee/ZigbeeDevice.h>

#include "../IO/AttributeDataContainer.h"
#include "Comand.h"

namespace zigbee {
class ZDevices;

class ComandFactory {
public:
	static Comand_P createComand(const std::string & code, ZDevices & zDevices, ZigbeeDevice & zigbeeDevice, AttributeDataContainer  & attributeDataContainer);
	static std::vector<Comand_P> createComands(const std::string & code, ZDevices & zDevices, ZigbeeDevice & zigbeeDevice, AttributeDataContainer  & attributeDataContainer);
};

} /* namespace zigbee */

#endif /* SRC_COMAND_COMANDFACTORY_H_ */
