//
// Created by paolo on 19/10/17.
//

#ifndef DOMUS_ENGINE_DEMODRIVERFACTORY_H
#define DOMUS_ENGINE_DEMODRIVERFACTORY_H

#include "../Utils/DriverFactory.h"
#include "DemoDevice.h"
#include <memory>


namespace zigbee {
    class DemoDriverFactory : public DriverFactory {
        std::string  getName() override {return "demo";}
        std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjectsImpl * singletonObjects) override {
            return  std::make_unique<DemoDevice>(*singletonObjects, singletonObjects->getConfiguration()->getRestTimeout());
        }
    };
}

#endif //DOMUS_ENGINE_DEMODRIVERFACTORY_H
