//
// Created by paolo on 11/05/17.
//

#include "../Utils/SingletonObjects.h"
#include "PowerNodeResponse2.h"

namespace zigbee {

    void PowerNodeResponse2::operator()(Packet &&packet) {
        auto powerNodeData = std::make_shared<PowerNodeData>();
        powerNodeData->nwkAddr = NwkAddr{packet.getUint16(1)};
        uint8_t mode = packet.getUint8(3);
        powerNodeData->powerMode = powerModefrom(mode >> 4);
        powerNodeData->availablePowerSource = PowerSource(mode & 0x0FF);
        uint8_t source = packet.getUint8(4);
        powerNodeData->currentPowerSource = PowerSource(source >> 4);
        powerNodeData->currentPowerSourceLevel = powerLevelFrom(source & 0xFF);
        singletons.getZigbeeDevice()->setPowerNode(powerNodeData);
    }
}