//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_DEVICEINFOEXECUTOR_H
#define DOMUS_ENGINE_DEVICEINFOEXECUTOR_H

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/DeviceInfoMessage.h>
#include "Executor.h"
#include "../Utils/SingletonObjectsImpl.h"
#include "../Utils/DeviceInfoDispatcher.h"

namespace zigbee {
    class DeviceInfoExecutor : public Executor {
    private:
        SingletonObjectsImpl &singletonObjects;

    public:
        DeviceInfoExecutor(SingletonObjectsImpl &singletonObjects) : singletonObjects{singletonObjects} {}

        virtual void operator()(unsigned char *data, int) override {
            DeviceInfoMessage *message = reinterpret_cast<DeviceInfoMessage *>(data);
            BOOST_LOG_TRIVIAL(info) << "Device info: address=" << (int)message->nwkAddr
                                    << " nodeRelation" << (int) message->nodeRelation
                                    << ", devStatus=" << (int) message->devStatus
                                    << ", assocCnt=" << (int) message->assocCnt
                                    << ", age=" << (int) message->age
                                    << ", txCounter=" << (int) message->txCounter
                                    << ", txCost" << (int) message->txCost
                                    << ", rxLqi" << (int) message->rxLqi;
            singletonObjects.getDeviceInfoDispatcher()->dispatch(message);
        }
    };

}


#endif //DOMUS_ENGINE_DEVICEINFOEXECUTOR_H
