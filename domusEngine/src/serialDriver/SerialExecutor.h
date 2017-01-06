//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_SERIALEXECUTOR_H
#define DOMUS_ENGINE_SERIALEXECUTOR_H


#include <string>

namespace zigbee {
    class SerialExecutor {
    public:
        virtual void operator()(const std::string &)=0;
    };
}


#endif //DOMUS_ENGINE_SERIALEXECUTOR_H
