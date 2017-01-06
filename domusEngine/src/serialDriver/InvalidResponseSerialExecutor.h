//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_INVALIDRESPONSESERIALEXECUTOR_H
#define DOMUS_ENGINE_INVALIDRESPONSESERIALEXECUTOR_H

#include <boost/log/trivial.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"
namespace zigbee {
    class InvalidResponseSerialExecutor : public SerialExecutor {
    public:
        virtual void operator()(const std::string & msg) override {
            BOOST_LOG_TRIVIAL(error) << "Invalid message from driver: " << msg;
        }
    };
}

#endif //DOMUS_ENGINE_INVALIDRESPONSESERIALEXECUTOR_H
