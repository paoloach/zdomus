//
// Created by paolo on 30/01/18.
//

#ifndef DOMUS_ENGINE_NODEDESCRIPTIONRESPONSE2_H
#define DOMUS_ENGINE_NODEDESCRIPTIONRESPONSE2_H

#include "Serial2Executor.h"

namespace zigbee {
    class SingletonObjects;

    class NodeDescriptionResponse2: public Serial2Executor {
    public:
        NodeDescriptionResponse2(SingletonObjects * singletons) : singletons(singletons) {}

        virtual void operator()(Packet && packet) override;

    private:
        SingletonObjects * singletons;

    };
}


#endif //DOMUS_ENGINE_NODEDESCRIPTIONRESPONSE2_H
