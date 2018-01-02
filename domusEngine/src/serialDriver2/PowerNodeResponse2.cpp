//
// Created by paolo on 11/05/17.
//

#include "../Utils/SingletonObjectsImpl.h"
#include "PowerNodeResponse2.h"

namespace zigbee {

    void PowerNodeResponse2::operator()(Packet &&packet) {
        auto powerNodeData = std::make_shared<PowerNodeData>();
        powerNodeData->nwkAddr = NwkAddr{packet.getUint16(1)};
        uint8_t mode = packet.getUint8(3);
        powerNodeData->powerMode = powerModefrom(mode & 0x0f);
        powerNodeData->availablePowerSource = PowerSource(mode >> 4);
        uint8_t source = packet.getUint8(4);
        powerNodeData->currentPowerSource = PowerSource(source & 0x0F);
        powerNodeData->currentPowerSourceLevel = powerLevelFrom(source >> 4);
        singletons.getZigbeeDevice()->setPowerNode(powerNodeData);
    }
}