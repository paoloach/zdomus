//
// Created by paolo on 22/09/16.
//

#ifndef ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
#define ZIGBEE_LIB_IEEEADDRESSRESPONSE_H

#include <set>
#include <zigbee/NwkAddr.h>
#include "ExtAddress.h"

namespace zigbee {
    struct  IEEEAddrResp {
        ExtAddress ieeeAddr;
        NwkAddr nwkAddr;
        uint8_t startIndex;
        std::set<NwkAddr> children;
    };

}

#endif //ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
