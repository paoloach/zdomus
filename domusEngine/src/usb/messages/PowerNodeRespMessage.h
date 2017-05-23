//
// Created by paolo on 23/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPMESSAGE_H
#define DOMUS_ENGINE_POWERNODERESPMESSAGE_H

#include <zigbee/messageStructure/GenericMessage.h>


namespace zigbee {
    struct __attribute__ ((__packed__)) PowerNodeRespMessage {
        GenericMessage genericDataMsg;
        uint16_t nwkAddr;
        uint8_t powerMode;
        uint8_t availablePowerSource;
        uint8_t currentPowerSource;
        uint8_t currentLevel;
    };
}

#endif //DOMUS_ENGINE_POWERNODERESPMESSAGE_H
