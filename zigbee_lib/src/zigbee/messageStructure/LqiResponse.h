//
// Created by paolo on 12/02/18.
//

#ifndef ZIGBEE_LIB_LQIRESPONSE_H
#define ZIGBEE_LIB_LQIRESPONSE_H

#include <ostream>
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

    inline std::ostream & operator<<(std::ostream & output, Relationship relationship){
        switch (relationship){
            case Relationship::NeighborIsParent:
                output << "NeighborIsParent";
                break;
            case Relationship::NeighborIsChild:
                output << "NeighborIsChild";
                break;
            case Relationship::NeighborIsSibling:
                output << "NeighborIsSibling";
                break;
            case Relationship::NoRelation:
                output << "NoRelation";
                break;
            case Relationship::PreviousChild:
                output << "PreviousChild";
                break;
            default:
                output << "Undefined";
                break;
        }
        return output;
    }

    struct LqiTable {
        friend std::ostream &operator<<(std::ostream &os, const LqiTable &table) {
            os << "panAddr: " << table.panAddr << " ieeeAddr: " << table.ieeeAddr << " nwkAddr: " << table.nwkAddr
               << " logicalType: " << table.logicalType << " onWhenIdle: " << table.onWhenIdle << " relationship: "
               << table.relationship << " neighborAcceptJoin: " << table.neighborAcceptJoin << " depth: " << table.depth
               << " lqi: " << table.lqi << " index: " << table.index;
            return os;
        }

        ExtAddress panAddr;
        ExtAddress ieeeAddr;
        NwkAddr nwkAddr;
        LogicalType logicalType;
        bool onWhenIdle;
        Relationship relationship;
        bool neighborAcceptJoin;
        uint depth;
        uint lqi;
        uint index;
    };


    class LqiResponse {
    public:
        friend std::ostream &operator<<(std::ostream &os, const LqiResponse &response) {
            os << "ownerNwkAddr: " << response.ownerNwkAddr << " totalTables: " << response.totalTables << " tables: ";
            for(auto & lqiTable: response.tables){
                os << "{" << lqiTable << "}  ";
            }
            return os;
        }

    public:
        NwkAddr ownerNwkAddr;

        uint totalTables;
        std::vector<LqiTable> tables;
    };


}


#endif //ZIGBEE_LIB_LQIRESPONSE_H
