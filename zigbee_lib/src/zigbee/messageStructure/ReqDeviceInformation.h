//
// Created by paolo on 19/09/16.
//

#ifndef ZIGBEE_LIB_REQDEVICEINFORMATION_H
#define ZIGBEE_LIB_REQDEVICEINFORMATION_H

#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {

    struct __attribute__ ((__packed__)) ReqDeviceInformation {
        ReqDeviceInformation(ZigbeeNwkAddress nwkAddr):nwkAddr(nwkAddr){
            generticDataMsg.msgCode = DEVICE_INFO;
        }

        GenericMessage generticDataMsg;
        ZigbeeNwkAddress nwkAddr;
    };

}

#endif //ZIGBEE_LIB_REQDEVICEINFORMATION_H
