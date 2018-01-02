//
// Created by paolo on 23/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSE2ERROR_H
#define DOMUS_ENGINE_POWERNODERESPONSE2ERROR_H

#include "Serial2Executor.h"

namespace zigbee {
    class SingletonObjectsImpl;

    class PowerNodeResponse2Error : public Serial2Executor {
    public:
        PowerNodeResponse2Error(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        void operator()(Packet && packet) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSE2ERROR_H
