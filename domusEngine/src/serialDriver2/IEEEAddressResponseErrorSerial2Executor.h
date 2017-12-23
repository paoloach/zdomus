//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIAL2EXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIAL2EXECUTOR_H

#include <boost/log/trivial.hpp>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjects.h"
namespace zigbee {
    class IEEEAddressResponseErrorSerial2Executor : public Serial2Executor {
    public:
        virtual void operator()(Packet && ) override {
            BOOST_LOG_TRIVIAL(error) << "Error requesting an IEEE address";
        }
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSEERRORSERIAL2EXECUTOR_H
