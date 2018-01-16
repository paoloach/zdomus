//
// Created by paolo on 07/01/17.
//

#ifndef DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H
#define DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H

#include "Serial2Executor.h"


namespace zigbee {
    class SingletonObjects;
    class DeviceInfoSerial2Executor : public Serial2Executor {
    public:
        DeviceInfoSerial2Executor(SingletonObjects * singletons) : singletons(singletons) {}
        void operator()(Packet &&packet) override ;
    private:
        SingletonObjects * singletons;
    };
}

#endif //DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H
