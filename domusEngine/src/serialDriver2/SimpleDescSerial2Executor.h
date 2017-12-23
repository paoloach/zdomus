//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_SIMPLEDESCSERIAL2EXECUTOR_H
#define DOMUS_ENGINE_SIMPLEDESCSERIAL2EXECUTOR_H



#include "Serial2Executor.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    class SingletonObjects;

    class SimpleDescSerial2Executor : public Serial2Executor {
    public:
        SimpleDescSerial2Executor(SingletonObjects &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override;

    private:
        SingletonObjects &singletons;
    };
}


#endif //DOMUS_ENGINE_SIMPLEDESCSERIALEXECUTOR_H
