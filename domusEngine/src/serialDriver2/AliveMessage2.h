//
// Created by paolo on 20/10/17.
//

#ifndef DOMUS_ENGINE_ALIVEMESSAGE2_H
#define DOMUS_ENGINE_ALIVEMESSAGE2_H

#include "Serial2Executor.h"
namespace zigbee {
    class AliveMessage2 : public Serial2Executor {
    public:
        virtual void operator()(Packet && ) override;
    };
}

#endif //DOMUS_ENGINE_ALIVEMESSAGE_H
