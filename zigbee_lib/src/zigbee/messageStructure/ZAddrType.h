/*
 * ZAddrType.h
 *
 *  Created on: 04/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_MESSAGESTRUCTURE_ZADDRTYPE_H_
#define SRC_ZIGBEE_MESSAGESTRUCTURE_ZADDRTYPE_H_

#include "../zigbeeConfig.h"

namespace zigbee {

struct __attribute__ ((__packed__)) ZAddrType {
	enum AddressMode {
		AddrNotPresent = 0, AddrGroup = 1, Addr16Bit = 2, Addr64Bit = 3, AddrBroadcast = 15
	};

	union {
		uint16_t shortAddr;
		uint8_t extAddr[Z_EXTADDR_LEN];
	} addr;
	uint8_t addrMode;
};

}

#endif /* SRC_ZIGBEE_MESSAGESTRUCTURE_ZADDRTYPE_H_ */
