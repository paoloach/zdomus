//
// Created by paolo on 22/09/16.
//

#ifndef ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
#define ZIGBEE_LIB_IEEEADDRESSRESPONSE_H

#include <set>
#include "zigbee/ExtAddress.h"
#include "../NwkAddr.h"
#include "ZAddrType.h"
#include "GenericMessage.h"
#include "../zigbeeConfig.h"

namespace zigbee {
    struct  IEEEAddressResponse {
        ExtAddress ieeeAddr;
        NwkAddr nwkAddr;
        uint startIndex;
        uint totalDevice;
        std::set<NwkAddr> children;
    };

}

#endif //ZIGBEE_LIB_IEEEADDRESSRESPONSE_H
