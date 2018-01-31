//
// Created by paolo on 23/12/17.
//
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>

#include "AliveMessage2.h"

namespace zigbee {
    void AliveMessage2::operator()(Packet && packet)  {
        uint dataSize = packet.getUint8(17);
        BOOST_LOG_TRIVIAL(info) << "mem used: " << packet.getUint16(1)
                                << ", block used: " << packet.getUint16(3)
                                << ", maxDataSize " << (int)packet.getUint8(5)
                                << ", maxBufferUsed " << (int)packet.getUint8(6)
                                << ", rxData1Count: " << packet.getUint16(7)
                                << ", rxData2Count: " << packet.getUint16(9)
                                << ", rxData3Count: " << packet.getUint16(11)
                                << ", rxDataOutOfBuffer: " << packet.getUint16(13)
                                << ", rxDataError: " << packet.getUint16(15)
                                << ", errorDataSize: " << dataSize;
        if (dataSize>0){
            std::stringstream str;
            for(uint i=18; i < 18+dataSize; i++){
                str << std::hex << std::setw(2) << std::setfill('0') << (int)packet.getUint8(i)<< " ";
            }
            BOOST_LOG_TRIVIAL(info) << "errorData: " << str.str();
        }
    }
}