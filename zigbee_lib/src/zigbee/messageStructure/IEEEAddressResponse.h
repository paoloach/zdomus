//
// Created by paolo on 22/09/16.
//

#ifndef ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
#define ZIGBEE_LIB_IEEEADDRESSRESPONSE_H

#include <vector>
#include "../NwkAddr.h"
#include "ZAddrType.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {
    struct  IEEEAddressResponse {
        GenericMessage generticDataMsg;
        uint8_t ieeeAddr[Z_EXTADDR_LEN];
        NwkAddr nwkAddr;
        uint8_t startIndex;
        std::vector<NwkAddr> childs;
    };

}

#endif //ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
