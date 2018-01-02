//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_ANNUNCESERIAL2EXECUTOR_H
#define DOMUS_ENGINE_ANNUNCESERIAL2EXECUTOR_H


#include "Serial2Executor.h"
#include "../Utils/SingletonObjectsImpl.h"

namespace zigbee {
    class AnnunceSerial2Executor : public Serial2Executor {
    public:
        AnnunceSerial2Executor(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}

#endif //DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
