//
// Created by paolo on 19/09/16.
//

#ifndef ZIGBEE_LIB_DEVICEINFOEMESSAGE_H
#define ZIGBEE_LIB_DEVICEINFOEMESSAGE_H

#include "GenericMessage.h"

namespace zigbee {
    struct __attribute__ ((__packed__)) DeviceInfoMessage {
        DeviceInfoMessage() : nwkAddr{0xFFFF}, nodeRelation{0}, devStatus{0}, assocCnt{0}, age{0}, txCounter{0},
                              txCost{0}, rxLqi{0} {
        }

        GenericMessage generticDataMsg;
        uint16_t nwkAddr;
        uint8_t nodeRelation;
        uint8_t devStatus;
        uint8_t assocCnt;
        uint8_t age;
        uint8_t txCounter;    // Counter of transmission success/failures
        uint8_t txCost;       // Average of sending rssi values if link staus is enabled i.e. NWK_LINK_STATUS_PERIOD is defined as non zero
        uint8_t rxLqi;        // average of received rssi values needs to be converted to link cost (1-7) before used
    };

}

#endif //ZIGBEE_LIB_DEVICEINFO_H
