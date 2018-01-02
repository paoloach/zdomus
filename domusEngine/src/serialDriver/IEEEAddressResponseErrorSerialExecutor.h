//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIALEXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIALEXECUTOR_H

#include <boost/log/trivial.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"
namespace zigbee {
    class IEEEAddressResponseErrorSerialExecutor : public SerialExecutor {
    public:
        virtual void operator()(const std::string & ) override {
            BOOST_LOG_TRIVIAL(error) << "Error requesting an IEEE address";
        }
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIALEXECUTOR_H
