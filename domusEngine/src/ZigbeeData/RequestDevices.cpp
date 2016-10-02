//
// Created by paolo on 28/09/16.
//

#include "RequestDevices.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/ZDevices.h"
#include <zigbee/ZigbeeDevice.h>

void zigbee::RequestDevices::requests() {
    requestThread = std::thread([this](){this->manageRequest();});
}

void zigbee::RequestDevices::manageRequest() {
    auto  devices = singletonObjects.getZDevices();
    auto zigbeeDevice = singletonObjects.getZigbeeDevice();

    for(auto & device: devices->getDevices()){
        zigbeeDevice->requestActiveEndpoints(device->getNwkAddr());
        sleep(1);
    }
}

void zigbee::RequestDevices::request(zigbee::ZDevice *zDevice) {
    if (zDevice->getNwkAddr().getId() == 0){
        return;
    }
    auto zigbeeDevice = singletonObjects.getZigbeeDevice();
    zigbeeDevice->requestActiveEndpoints(zDevice->getNwkAddr());
}
