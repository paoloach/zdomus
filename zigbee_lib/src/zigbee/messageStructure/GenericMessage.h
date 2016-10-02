/*
 * GenericMessage.h
 *
 *  Created on: 17/lug/2014
 *      Author: paolo
 */

#ifndef GENERICMESSAGE_H_
#define GENERICMESSAGE_H_

#include <cstdint>


namespace zigbee {

struct __attribute__ ((__packed__)) GenericMessage {
	GenericMessage()= default;
	GenericMessage(uint8_t msgCode):msgCode(msgCode){}
	uint8_t msgCode;
};

}


#endif /* GENERICMESSAGE_H_ */
