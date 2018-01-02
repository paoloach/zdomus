//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
#define DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H


#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"

namespace zigbee {
    class AnnunceSerialExecutor : public SerialExecutor {
    public:
        AnnunceSerialExecutor(SingletonObjectsImpl &singletons) : singletons(singletons) {}
        virtual void operator()(const std::string &msg) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}

#endif //DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
