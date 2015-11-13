/*
 * InvalidZEndpointException.h
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZENDPOINTEXCEPTION_H_
#define SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZENDPOINTEXCEPTION_H_

#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>

#include "ZigbeeDeviceException.h"


namespace zigbee {

class InvalidZEndpointException  : public ZigbeeDeviceException {
public:
	InvalidZEndpointException(NwkAddr nwkAddress,EndpointID endpoint);
	virtual ~InvalidZEndpointException();
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_EXCEPTIONS_INVALIDZENDPOINTEXCEPTION_H_ */
