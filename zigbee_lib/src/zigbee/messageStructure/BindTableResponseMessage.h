/*
 * BindTableResponseMessage.h
 *
 *  Created on: 04/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_MESSAGESTRUCTURE_BINDTABLERESPONSEMESSAGE_H_
#define SRC_ZIGBEE_MESSAGESTRUCTURE_BINDTABLERESPONSEMESSAGE_H_

#include "ZAddrType.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {

struct __attribute__ ((__packed__)) BindTableResponseMessage {
	GenericMessage generticDataMsg;
	uint8_t srcAddr[Z_EXTADDR_LEN]; // Src address
	uint8_t srcEP;                   // Endpoint/interface of source device
	uint16_t clusterID;             // ClusterImpl ID
	uint16_t dstAddr;          // Destination address
	uint8_t dstEP;                   // Endpoint/interface of dest device
};

}



#endif /* SRC_ZIGBEE_MESSAGESTRUCTURE_BINDTABLERESPONSEMESSAGE_H_ */
