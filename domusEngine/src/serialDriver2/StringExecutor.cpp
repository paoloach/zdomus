//
// Created by paolo on 23/12/17.
//
#include <boost/log/trivial.hpp>
#include "StringExecutor.h"

void zigbee::StringExecutor::operator()(zigbee::Packet && packet) {
    auto data = std::make_unique<char[]>(packet.size());
    std::copy(packet.begin()+1, packet.end(), data.get());
    data.get()[packet.size()-1] = 0;
    BOOST_LOG_TRIVIAL(info) << data.get();
}
