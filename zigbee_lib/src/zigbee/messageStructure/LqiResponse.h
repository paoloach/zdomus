//
// Created by paolo on 12/02/18.
//

#ifndef ZIGBEE_LIB_LQIRESPONSE_H
#define ZIGBEE_LIB_LQIRESPONSE_H

#include <sys/types.h>
#include "../ExtAddress.h"
#include "../NwkAddr.h"
#include "NodeDescriptorResponse.h"

namespace zigbee {
    enum class Relationship {
        NeighborIsParent,
        NeighborIsChild,
        NeighborIsSibling,
        NoRelation,
        PreviousChild
    };

    class LqiResponse {
    public:
        uint index;
        uint totalTables;
        ExtAddress panAddr;
        ExtAddress ieeeAddr;
        NwkAddr nwkAddr;
        LogicalType logicalType;
        bool onWhenIdle;
        Relationship relationship;
        bool neighborAcceptJoin;
        uint depth;
        uint lqi;

    };
}


#endif //ZIGBEE_LIB_LQIRESPONSE_H
