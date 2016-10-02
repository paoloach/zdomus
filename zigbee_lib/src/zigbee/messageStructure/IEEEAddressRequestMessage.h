//
// Created by paolo on 22/09/16.
//

#ifndef ZIGBEE_LIB_IEEEADDRESSREQUESTMESSAGE_H
#define ZIGBEE_LIB_IEEEADDRESSREQUESTMESSAGE_H

#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {

    struct __attribute__ ((__packed__)) IEEEAddressRequestMessage {
        IEEEAddressRequestMessage(ZigbeeNwkAddress nwkAddr, uint8_t requestType, uint8_t startIndex) : nwkAddr(nwkAddr),
                                                                                                       requestType(
                                                                                                               requestType),
                                                                                                       startIndex(
                                                                                                               startIndex) {
            genericDataMsg.msgCode = REQ_IEEE_ADDRESS;
        }

        GenericMessage genericDataMsg;
        uint16_t nwkAddr;
        uint8_t requestType;
        uint8_t startIndex;
    };

}

#endif //ZIGBEE_LIB_IEEEADDRESSREQUESTMESSAGE_H
