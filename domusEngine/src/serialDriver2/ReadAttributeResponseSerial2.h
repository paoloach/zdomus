//
// Created by paolo on 04/01/17.
//

#ifndef DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL2_H
#define DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL2_H

#include "Serial2Executor.h"
#include "../Utils/SingletonObjectsImpl.h"


namespace zigbee {
    class ReadAttributeResponseSerial2 : public Serial2Executor {
    public:
        ReadAttributeResponseSerial2(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}

#endif //DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL2_H
