//
// Created by paolo on 13/02/18.
//

#ifndef DOMUS_ENGINE_LQIRESPONSESERIAL2_H
#define DOMUS_ENGINE_LQIRESPONSESERIAL2_H

#include "Serial2Executor.h"

namespace zigbee {
    class SingletonObjects;
    class LQIResponseSerial2 : public Serial2Executor{
    public:
        LQIResponseSerial2(SingletonObjects * singletons) : singletons(singletons) {}

        virtual void operator()(Packet && packet) override;

    private:
        SingletonObjects * singletons;
    };
}


#endif //DOMUS_ENGINE_LQIRESPONSESERIAL2_H
