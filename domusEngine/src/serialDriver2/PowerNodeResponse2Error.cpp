//
// Created by paolo on 23/05/17.
//

#include <boost/log/trivial.hpp>
#include <zcl/Cluster.h>
#include <zigbee/PowerNodeData.h>
#include <zigbee/messageStructure/ActiveEPErrorMessage.h>
#include "PowerNodeResponse2Error.h"
#include "../Utils/SingletonObjectsImpl.h"


void zigbee::PowerNodeResponse2Error::operator()(Packet &&packet) {
    auto powerNodeData = std::make_shared<PowerNodeData>();
    powerNodeData->nwkAddr = NwkAddr{packet.getUint16(1)};
    auto status = packet.getUint8(3);
    BOOST_LOG_TRIVIAL(error) << "error requesting power node for device " << std::hex << powerNodeData->nwkAddr << " because " << errorCodeToString(status);
    powerNodeData->error = true;

    singletons->getZigbeeDevice()->setPowerNode(powerNodeData);
}
