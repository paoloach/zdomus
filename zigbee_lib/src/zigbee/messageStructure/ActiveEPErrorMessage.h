//
// Created by paolo on 14/06/16.
//

#ifndef ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H
#define ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H

#include "GenericMessage.h"

namespace zigbee {


struct __attribute__ ((__packed__)) ActiveEPErrorMessage {
	GenericMessage generticDataMsg;
	uint16_t	nwkAddr;
	uint8_t  	errorCode;
};

}

#endif //ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H
