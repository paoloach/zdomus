/*
 * ReqSimpleDescMessage.h
 *
 *  Created on: 20/lug/2014
 *      Author: paolo
 */

#ifndef __REQ_ACTIVE_ENDPOINTS_MESSAGE__H__
#define __REQ_ACTIVE_ENDPOINTS_MESSAGE__H__

#include "../zigbeeConfig.h"

namespace zigbee {


struct __attribute__ ((__packed__)) ReqActiveEndpointsMessage {
	ReqActiveEndpointsMessage() {
		generticDataMsg.msgCode = REQ_ACTIVE_ENDPOINTS;
	}
	GenericMessage generticDataMsg;
	uint16_t     nwkAddr;
};

}




#endif /* REQSIMPLEDESCMESSAGE_H_ */
