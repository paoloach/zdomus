//
// Created by paolo on 11/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSE2_H
#define DOMUS_ENGINE_POWERNODERESPONSE2_H


#include "Serial2Executor.h"

namespace zigbee {
    class SingletonObjects;
    class PowerNodeResponse2 : public Serial2Executor {
    public:
        PowerNodeResponse2(SingletonObjects &singletons) : singletons(singletons) {}

        virtual void operator()(Packet && packet) override;

    private:
        SingletonObjects &singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSE2_H
