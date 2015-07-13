/*
 * zclDevice.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLDEVICE_H_
#define ZCLDEVICE_H_

#include "../zigbee/messageStructure/SimpleDescMessage.h"

namespace zigbee {

class zclDevice {
public:
	zclDevice(SimpleDescMessage * simpleDesc);
	virtual ~zclDevice();
protected:
	uint16_t networkAddr;
	uint8_t  endpoint;
};

} /* namespace zigbee */

#endif /* ZCLDEVICE_H_ */
