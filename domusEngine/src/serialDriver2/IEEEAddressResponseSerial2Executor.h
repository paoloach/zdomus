//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSESERIAL2EXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSESERIAL2EXECUTOR_H


#include "Serial2Executor.h"


namespace zigbee {
    class SingletonObjects;
    class IEEEAddressResponseSerial2Executor : public Serial2Executor {
    public:
        IEEEAddressResponseSerial2Executor(SingletonObjects * singletonObjects) : singletonObjects(singletonObjects) {}

        void operator()(Packet &&packet) override;

    private:
        SingletonObjects * singletonObjects;
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
