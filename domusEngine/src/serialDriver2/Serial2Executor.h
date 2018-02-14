//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_SERIAL2EXECUTOR_H
#define DOMUS_ENGINE_SERIAL2EXECUTOR_H


#include <string>
#include "Packet.h"

namespace zigbee {
    class Serial2Executor {
    public:
        virtual void operator()(Packet &&packet)=0;
    };
}


#endif //DOMUS_ENGINE_SERIALEXECUTOR_H
