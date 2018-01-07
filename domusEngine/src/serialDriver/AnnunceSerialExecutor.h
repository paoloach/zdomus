//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
#define DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H


#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class AnnunceSerialExecutor : public SerialExecutor {
    public:
        AnnunceSerialExecutor(SingletonObjects *singletons) : singletons(singletons) {}

        virtual void operator()(const std::string &msg) override;

    private:
        SingletonObjects *singletons;
    };
}

#endif //DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
