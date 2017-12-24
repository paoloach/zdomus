//
// Created by paolo on 23/12/17.
//
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>

#include "AliveMessage2.h"

namespace zigbee {
    void AliveMessage2::operator()(Packet && packet)  {
        BOOST_LOG_TRIVIAL(info) << "mem used: " << packet.getUint16(1)
                                << ", block used: " << packet.getUint16(3)
                                << ", maxDataSize " << (int)packet.getUint8(5)
                                << ", maxBufferUsed " << (int)packet.getUint8(6);
    }
}