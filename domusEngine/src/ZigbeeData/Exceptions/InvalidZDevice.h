/*
 * InvalidZDevice.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZDEVICE_H_
#define SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZDEVICE_H_

#include "../ExtAddress.h"
#include <zigbee/NwkAddr.h>
#include "ZigbeeDeviceException.h"

namespace zigbee {

class InvalidZDevice : public ZigbeeDeviceException {
public:
	InvalidZDevice(const ExtAddress & extAddress);
	InvalidZDevice(NwkAddr shortAddress);
	~InvalidZDevice() override;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZDEVICE_H_ */
