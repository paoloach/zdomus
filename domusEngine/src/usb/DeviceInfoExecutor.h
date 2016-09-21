//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_DEVICEINFOEXECUTOR_H
#define DOMUS_ENGINE_DEVICEINFOEXECUTOR_H

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/DeviceInfoMessage.h>
#include "Executor.h"
#include "../Utils/SingletonObjects.h"
#include "../Utils/DeviceInfoDispatcher.h"

namespace zigbee {
    class DeviceInfoExecutor : public Executor {
    private:
        SingletonObjects &singletonObjects;

    public:
        DeviceInfoExecutor(SingletonObjects & singletonObjects):singletonObjects{singletonObjects}{}

        virtual void operator()(unsigned char *data, int) override {
            DeviceInfoMessage * message = reinterpret_cast<DeviceInfoMessage *>(data);
            singletonObjects.getDeviceInfoDispatcher()->dispatch(message);
        }
    };

}


#endif //DOMUS_ENGINE_DEVICEINFOEXECUTOR_H
