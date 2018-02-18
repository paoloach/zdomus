//
// Created by paolo on 13/02/18.
//

#include "lQINotSupported2.h"
#include "../Utils/SingletonObjectsImpl.h"

// if not supported
//   1 byte -> MgmqLqiNotSupported
//   2 bytes ->networkd id (1)
void zigbee::LQINotSupported2::operator()(zigbee::Packet &&packet) {
    BOOST_LOG_TRIVIAL(info) << "LQI Not supported response arrived";

    auto response = std::make_shared<LqiResponse>();
    response->ownerNwkAddr = NwkAddr{packet.getUint16(1)};
    singletons->getZigbeeDevice()->setLQIResponse(response);
}
