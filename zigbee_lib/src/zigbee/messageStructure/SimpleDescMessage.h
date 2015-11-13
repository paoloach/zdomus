/*
 * SimpleDescMessage.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef SIMPLEDESCMESSAGE_H_
#define SIMPLEDESCMESSAGE_H_

#include "../zigbeeConfig.h"
#include "GenericMessage.h"

namespace zigbee {

#define MAX_CLUSTERS 20

struct __attribute__ ((__packed__)) SimpleDescMessage {
	GenericMessage generticDataMsg;
	uint16_t nwkAddr;
	uint8_t endpoint;
	uint16_t appProfId;
	uint16_t appDeviceId;
	uint8_t appDevVer;
	uint8_t numInClusters;
	uint8_t numOutClusters;
	uint16_t clustersList[MAX_CLUSTERS];
};

}

#endif /* SIMPLEDESCMESSAGE_H_ */
