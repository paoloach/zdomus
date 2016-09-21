//
// Created by paolo on 19/09/16.
//

#include "DeviceInfoDispatcher.h"

namespace zigbee {
    void
    DeviceInfoDispatcher::add(DeviceInfoDispatcher::DeviceInfoObserver * observer, NwkAddr address) {
        if (observer != nullptr) {
            observers[address].insert(observer);
        }
    }

    void
    DeviceInfoDispatcher::remove( DeviceInfoDispatcher::DeviceInfoObserver * observer, NwkAddr address) {
        if (observer != nullptr) {
            observers[address].erase(observer);
        }
    }

    void DeviceInfoDispatcher::dispatch(DeviceInfoMessage *deviceInfo) {
        NwkAddr nwkAddr(deviceInfo->nwkAddr);
        for (DeviceInfoDispatcher::DeviceInfoObserver* observer: observers[nwkAddr]){
            observer->newDeviceInfo(deviceInfo);
        }
    }

}
