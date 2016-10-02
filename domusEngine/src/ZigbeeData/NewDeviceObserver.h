//
// Created by paolo on 26/09/16.
//

#ifndef DOMUS_ENGINE_NEWDEVICEOBSERVER_H
#define DOMUS_ENGINE_NEWDEVICEOBSERVER_H

#include <memory>
#include "ZDevice.h"

namespace zigbee {
    class NewDeviceObserver {
        virtual void newDevice(std::shared_ptr<ZDevice> device)=0;
    };
}

#endif //DOMUS_ENGINE_NEWDEVICEOBSERVER_H
