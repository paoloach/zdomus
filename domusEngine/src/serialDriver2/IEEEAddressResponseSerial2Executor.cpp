//
// Created by paolo on 17/01/18.
//
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zigbee/messageStructure/IEEEAddressResponse.h>
#include <zigbee/ZigbeeDevice.h>
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/ZDevices.h"
#include "IEEEAddressResponseSerial2Executor.h"

namespace  zigbee {
    void IEEEAddressResponseSerial2Executor::operator()(Packet &&packet)  {
        BOOST_LOG_NAMED_SCOPE("serial driver");
        auto message = std::make_shared<IEEEAddressResponse>();
        try {

            message->ieeeAddr = packet.getExtAddress(1);
            message->nwkAddr = NwkAddr(packet.getUint16(9));
            message->totalDevice  =  packet[11];
            message->startIndex  =  packet[12];
            int numChildren = packet[13];

            for (int i = 0; i < numChildren; i++) {
                message->children.emplace(packet.getUint16(14+2*i));
            }
            singletonObjects->getZigbeeDevice()->setIEEEAddress(message);
            singletonObjects->getZDevices()->addDeviceInfo(message.get());
        } catch (std::exception &e) {
            BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
        }
    }
}