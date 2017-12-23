//
// Created by paolo on 23/12/17.
//

#ifndef DOMUS_ENGINE_STRINGEXECUTOR_H
#define DOMUS_ENGINE_STRINGEXECUTOR_H

#include "Serial2Executor.h"
namespace zigbee {
    class StringExecutor : public Serial2Executor{
    public:
        virtual void operator()(Packet && ) override;
    };
}


#endif //DOMUS_ENGINE_STRINGEXECUTOR_H
