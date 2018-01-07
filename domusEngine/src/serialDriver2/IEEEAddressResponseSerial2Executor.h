//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSESERIAL2EXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSESERIAL2EXECUTOR_H

#include <boost/log/trivial.hpp>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/IEEEAddressResponse.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    class IEEEAddressResponseSerial2Executor : public Serial2Executor {
    public:
        IEEEAddressResponseSerial2Executor(SingletonObjects * singletonObjects) : singletonObjects(singletonObjects) {}

        virtual void operator()(Packet &&packet) override {
            BOOST_LOG_NAMED_SCOPE("serial driver");
            IEEEAddrResp message;
            try {

                message.ieeeAddr = packet.getExtAddress(1);
                message.nwkAddr = NwkAddr(packet.getUint16(9));

                message.startIndex  =  packet[12];
                int numChildren = packet[13];

                for (int i = 0; i < numChildren; i++) {
                    message.children.emplace(packet.getUint16(14+2*i));
                }
                singletonObjects->getZDevices()->addDeviceInfo(message);
            } catch (std::exception &e) {
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjects * singletonObjects;
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
