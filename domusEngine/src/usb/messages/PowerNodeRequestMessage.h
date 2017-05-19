//
// Created by paolo on 19/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODEREQUESTMESSAGE_H
#define DOMUS_ENGINE_POWERNODEREQUESTMESSAGE_H

#include <zigbee/messageStructure/GenericMessage.h>
#include <zigbee/ZigbeeTypes.h>
#include <zigbee/zigbeeConfig.h>
#include "zigbeeConfig.h"

namespace zigbee {

    struct __attribute__ ((__packed__)) PowerNodeRequestMessage {
        PowerNodeRequestMessage(NwkAddr nwkAddr) : genericDataMsg(REQ_NODE_POWER), nwkAddr(nwkAddr.getId()) {
        }

        GenericMessage genericDataMsg;
        uint16_t nwkAddr;
    };

}

#endif //DOMUS_ENGINE_POWERNODEREQUESTMESSAGE_H
