//
// Created by paolo on 28/09/16.
//

#ifndef DOMUS_ENGINE_REQUESTDEVICES_H
#define DOMUS_ENGINE_REQUESTDEVICES_H

#include <thread>
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class ZDevice;

    class RequestDevices {
    private:
        SingletonObjects * singletonObjects;
        std::thread   requestThread;
    public:
        RequestDevices(SingletonObjects *singletonObjects) : singletonObjects(singletonObjects) {}

        void request(ZDevice * zDevice);
        void requests();

    private:
        void manageRequest();

    };
}


#endif //DOMUS_ENGINE_REQUESTDEVICES_H
