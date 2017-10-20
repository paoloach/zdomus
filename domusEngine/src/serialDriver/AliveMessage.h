//
// Created by paolo on 20/10/17.
//

#ifndef DOMUS_ENGINE_ALIVEMESSAGE_H
#define DOMUS_ENGINE_ALIVEMESSAGE_H

#include <string>
#include "SerialExecutor.h"
namespace zigbee {
    class AliveMessage : public SerialExecutor {
    public:
        virtual void operator()(const std::string & ) override {
        }
    };
}

#endif //DOMUS_ENGINE_ALIVEMESSAGE_H
