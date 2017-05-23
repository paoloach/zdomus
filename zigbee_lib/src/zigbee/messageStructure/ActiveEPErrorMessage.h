//
// Created by paolo on 14/06/16.
//

#ifndef ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H
#define ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H

#include <string>
#include "GenericMessage.h"


namespace zigbee {
    struct __attribute__ ((__packed__)) ActiveEPErrorMessage {
        GenericMessage genericDataMsg;
        uint16_t nwkAddr;
        uint8_t errorCode;
    };

    inline std::string errorCodeToString(uint8_t errorCode){
        switch (errorCode){
            case 0x02:
                return "invalid parameter";
            case 0x10:
                return "memory fail";
            case 0xCD:
                return  "no route";
            default:
                return  "error code " + std::to_string(errorCode);
        }
    }

}

#endif //ZIGBEE_LIB_ACTIVEEPERRORMESSAGE_H
