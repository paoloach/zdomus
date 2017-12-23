//
// Created by paolo on 18/10/17.
//

#ifndef DOMUS_ENGINE_SERIAL2DRIVERFACTORY_H
#define DOMUS_ENGINE_SERIAL2DRIVERFACTORY_H

#include "../Utils/DriverFactory.h"
#include "SerialDriver2.h"
#include <memory>

namespace zigbee {
    class SerialDriver2Factory : public DriverFactory {
        std::string  getName() override {return "serial2";}
        std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjects * singletonObjects) override {
            return  std::make_unique<SerialDriver2>("/dev/ttyUSB0", *singletonObjects, singletonObjects->getConfiguration()->getRestTimeout());
        }
    };
}

#endif //DOMUS_ENGINE_SERIALDRIVERFACTORY_H
