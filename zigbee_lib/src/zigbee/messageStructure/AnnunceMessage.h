/*
 * AnnunceMessage.h
 *
 *  Created on: 17/lug/2014
 *      Author: paolo
 */

#ifndef ANNUNCEMESSAGE_H_
#define ANNUNCEMESSAGE_H_

#include "../zigbeeConfig.h"
#include "GenericMessage.h"

namespace zigbee {


struct __attribute__ ((__packed__)) AnnunceMessage {
	GenericMessage generticDataMsg;
	uint16_t     nwkAddr;
 	uint8_t       extAddr[Z_EXTADDR_LEN];
 	uint8_t       capabilities;
};

}

#endif /* ANNUNCEMESSAGE_H_ */
