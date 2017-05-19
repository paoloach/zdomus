//
// Created by paolo on 10/05/17.
//

#ifndef DOMUS_ENGINE_REQNODEPOWERMESSAGE_H_H
#define DOMUS_ENGINE_REQNODEPOWERMESSAGE_H_H


#include <zigbee/messageStructure/GenericMessage.h>
#include <zigbee/zigbeeConfig.h>

namespace zigbee {


struct __attribute__ ((__packed__)) ReqNodePowerMessage {
    ReqNodePowerMessage(NwkAddr nwkAddr):genericDataMsg(REQ_NODE_POWER), nwkAddr(nwkAddr.getId()) {
	}
	GenericMessage genericDataMsg;
	uint16_t     nwkAddr;
};

}

#endif //DOMUS_ENGINE_REQNODEPOWERMESSAGE_H_H
