/*
 * zclDevice.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLDevice.h"

namespace zigbee {

zclDevice::zclDevice(SimpleDescMessage * simpleDesc) :networkAddr(simpleDesc->nwkAddr), endpoint(simpleDesc->endpoint){

}

zclDevice::~zclDevice() = default;

} /* namespace zigbee */
