//
// Created by paolo on 18/07/16.
//

#ifndef ZIGBEE_LIB_INFOMESSAGE_H
#define ZIGBEE_LIB_INFOMESSAGE_H

#include "GenericMessage.h"

namespace zigbee {
    struct __attribute__ ((__packed__)) InfoMessage {
        GenericMessage generticDataMsg;
        uint16_t	nwkAddr;
    };

}

#endif //ZIGBEE_LIB_INFOMESSAGE_H
