//
// Created by paolo on 07/01/17.
//

#ifndef DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H
#define DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H


#include <zigbee/NwkAddr.h>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjects.h"


namespace zigbee {
    class DeviceInfoSerial2Executor : public Serial2Executor {
    public:
        DeviceInfoSerial2Executor(SingletonObjects &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override {
            DeviceInfoMessage message;
            message.nwkAddr = packet.getUint16(1);
            message.nodeRelation = packet.getUint8(3);
            message.devStatus = packet.getUint8(4);
            message.assocCnt = packet.getUint8(5);
            message.age = packet.getUint8(6);
            message.txCounter = packet.getUint8(7);
            message.txCost = packet.getUint8(8);
            message.rxLqi = packet.getUint8(9);
            singletons.getDeviceInfoDispatcher()->dispatch(&message);
        }

    private:
        SingletonObjects &singletons;
    };
}

#endif //DOMUS_ENGINE_DEVICEINFOSERIAL2EXECUTOR_H
