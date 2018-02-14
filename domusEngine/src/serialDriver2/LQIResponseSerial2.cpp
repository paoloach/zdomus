//
// Created by paolo on 13/02/18.
//

#include "LQIResponseSerial2.h"
#include "../Utils/SingletonObjectsImpl.h"


namespace zigbee {


    static Relationship  toRelationship(uint value){
        switch (value){
            case 0:
                return Relationship::NeighborIsParent;
            case  1:
                return Relationship::NeighborIsChild;
            case  2:
                return Relationship::NeighborIsSibling;
            case 4:
                return Relationship::PreviousChild;
            default:
                return Relationship::NoRelation;
        }
    }
// if no error
//   1 byte  -> code MgmtLqi
//   2 bytes -> network id (1)
//   1 byte  -> total table entries (3)
//	 1 byte  -> start index  (4)
//   1 byte  -> response table count (5)
//   for every table
//   8 bytes -> pan ID			 (0)
//   8 bytes -> extended address (8)
//   2 bytes -> network address(16)
//   2 bits  -> neightbor device (18)
//   2 bits  -> rx On When Idle (18)
//   3 bits  -> relationship (18)
//   1 bit   -> reserveved(18)
//   2 bits  -> permit join (19)
//   6 bits  -> reserved(19)
//   1 byte  -> depth (20)
//   1 byte  -> LQI(21)
    void LQIResponseSerial2::operator()(zigbee::Packet &&packet) {

        BOOST_LOG_TRIVIAL(info) << "LQI response arrived";
        NwkAddr nwkAddr = NwkAddr{packet.getUint16(1)};
        uint totalTables = packet.getUint8(3);
        uint index = packet.getUint8(4);
        uint tablesSent = +packet.getUint8(5);
        for (uint i = 0; i < tablesSent; i++) {
            auto response = std::make_shared<LqiResponse>();
            response->nwkAddr = nwkAddr;
            response->totalTables = totalTables;
            response->index = i + index;
            uint offset = i * 22 + 6;
            response->panAddr = packet.getExtAddress(offset);
            response->ieeeAddr = packet.getExtAddress(offset + 8);
            response->nwkAddr = NwkAddr{packet.getUint16(16)};
            uint8_t flags = packet.getUint8(18);
            response->logicalType = toLogicalType(flags & 0b11);
            response->onWhenIdle = ((flags >> 2) & 0b11) == 1;
            response->relationship = toRelationship((flags >> 4) & 0b111);
            flags = packet.getUint8(19);
            response->neighborAcceptJoin = (flags >> 0b11)  == 1;
            response->depth = packet.getUint16(20);
            response->lqi = packet.getUint16(21);

            singletons->getZigbeeDevice()->setLQIResponse(response);
        }


    }
}