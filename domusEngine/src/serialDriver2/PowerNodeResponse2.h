//
// Created by paolo on 11/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSE2_H
#define DOMUS_ENGINE_POWERNODERESPONSE2_H


#include "Serial2Executor.h"

namespace zigbee {
    class SingletonObjectsImpl;
    class PowerNodeResponse2 : public Serial2Executor {
    public:
        PowerNodeResponse2(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        virtual void operator()(Packet && packet) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSE2_H
