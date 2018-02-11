//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_INVALIDRESPONSESERIAL2EXECUTOR_H
#define DOMUS_ENGINE_INVALIDRESPONSESERIAL2EXECUTOR_H

#include <boost/log/trivial.hpp>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjectsImpl.h"
namespace zigbee {
    class InvalidResponseSerial2Executor : public Serial2Executor {
    public:
        virtual void operator()(Packet && packet) override {
            BOOST_LOG_TRIVIAL(error) << "Invalid message from driver: code " << (int)packet.getCmdCode();
        }
    };
}

#endif //DOMUS_ENGINE_INVALIDRESPONSESERIAL2EXECUTOR_H
