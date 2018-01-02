//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_SIMPLEDESCSERIAL2EXECUTOR_H
#define DOMUS_ENGINE_SIMPLEDESCSERIAL2EXECUTOR_H



#include "Serial2Executor.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    class SingletonObjectsImpl;

    class SimpleDescSerial2Executor : public Serial2Executor {
    public:
        SimpleDescSerial2Executor(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}


#endif //DOMUS_ENGINE_SIMPLEDESCSERIALEXECUTOR_H
