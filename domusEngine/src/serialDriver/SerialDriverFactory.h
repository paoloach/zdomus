//
// Created by paolo on 18/10/17.
//

#ifndef DOMUS_ENGINE_SERIALDRIVERFACTORY_H
#define DOMUS_ENGINE_SERIALDRIVERFACTORY_H

#include "../Utils/DriverFactory.h"
#include "SerialDriver.h"
#include <memory>

namespace zigbee {
    class SerialDriverFactory : public DriverFactory {
        std::string  getName() override {return "serial";}
        std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjects * singletonObjects) override {
            return  std::make_unique<SerialDriver>("/dev/ttyUSB0", singletonObjects, singletonObjects->getConfiguration()->getRestTimeout());
        }
    };
}

#endif //DOMUS_ENGINE_SERIALDRIVERFACTORY_H
