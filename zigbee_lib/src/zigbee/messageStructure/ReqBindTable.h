/*
 * ReqBindTable.h
 *
 *  Created on: 04/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_MESSAGESTRUCTURE_REQBINDTABLE_H_
#define SRC_ZIGBEE_MESSAGESTRUCTURE_REQBINDTABLE_H_

#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {

struct __attribute__ ((__packed__)) ReqBindTable {
	ReqBindTable(ZigbeeNwkAddress nwkAddr):nwkAddr(nwkAddr){
		generticDataMsg.msgCode = REQ_SEND_CMD_VALUES;
	}


	GenericMessage generticDataMsg;
	ZigbeeNwkAddress nwkAddr;
};

}



#endif /* SRC_ZIGBEE_MESSAGESTRUCTURE_REQBINDTABLE_H_ */
