//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_USBRESPONSEEXECUTERS_H
#define DOMUS_ENGINE_USBRESPONSEEXECUTERS_H

#include <map>
#include <bits/unique_ptr.h>
#include "Executor.h"
#include "../ZigbeeData/ZDevices.h"
#include "../IO/AttributeDataContainer.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class DomusEngineUSBDevice;

    class UsbResponseExecutors {
    private:
        std::map<uint8_t, std::unique_ptr<Executor> > executors;
    public:
        UsbResponseExecutors(SingletonObjects &singletonObjects, DomusEngineUSBDevice &usbDevice);

        void execute(unsigned char *data, int length);
    };
}


#endif //DOMUS_ENGINE_USBRESPONSEEXECUTERS_H
