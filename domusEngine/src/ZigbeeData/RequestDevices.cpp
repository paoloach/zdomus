//
// Created by paolo on 28/09/16.
//

#include <boost/log/trivial.hpp>
#include "RequestDevices.h"
#include "../ZigbeeData/ZDevices.h"
#include <zigbee/ZigbeeDevice.h>

void zigbee::RequestDevices::requests() {
    requestThread = std::thread([this]() { this->manageRequest(); });
}

void zigbee::RequestDevices::manageRequest() {
    BOOST_LOG_TRIVIAL(info) << "Start requesting thread";
    auto devices = singletonObjects->getZDevices();
    auto zigbeeDevice = singletonObjects->getZigbeeDevice();

    for (auto &device: devices->getDevices()) {
        BOOST_LOG_TRIVIAL(info) << "requesting " << device->getNwkAddr();
        zigbeeDevice->requestActiveEndpoints(device->getNwkAddr());
        sleep(1);
    }
}

void zigbee::RequestDevices::request(zigbee::ZDevice *zDevice) {
    if (zDevice->getNwkAddr().getId() == 0) {
        return;
    }
    auto zigbeeDevice = singletonObjects->getZigbeeDevice();
    BOOST_LOG_TRIVIAL(info) << "Observer callback requesting " << std::hex << zDevice->getNwkAddr();
    zigbeeDevice->requestActiveEndpoints(zDevice->getNwkAddr());
}
