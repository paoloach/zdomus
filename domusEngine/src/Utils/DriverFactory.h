//
// Created by paolo on 18/10/17.
//

#ifndef DOMUS_ENGINE_DRIVERFACTORY_H
#define DOMUS_ENGINE_DRIVERFACTORY_H

#include <string>
#include <zigbee/ZigbeeDevice.h>
#include "SingletonObjects.h"

namespace zigbee {

    class DriverFactory {
    public:
        virtual std::string  getName() = 0;
        virtual std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjects * singletonObjects)=0;
    };
}


#endif //DOMUS_ENGINE_DRIVERFACTORY_H
