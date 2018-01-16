//
// Created by paolo on 14/01/18.
//

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/DeviceInfoMessage.h>
#include "DeviceInfoSerial2Executor.h"
#include "../Utils/SingletonObjects.h"
#include "../Utils/DeviceInfoDispatcher.h"

namespace zigbee {
    void DeviceInfoSerial2Executor::operator()(Packet &&packet) {
        BOOST_LOG_TRIVIAL(info) << "Device info: " << packet;
        DeviceInfoMessage message;
        message.nwkAddr = packet.getUint16(1);
        message.nodeRelation = packet.getUint8(3);
        message.devStatus = packet.getUint8(4);
        message.assocCnt = packet.getUint8(6);
        message.age = packet.getUint8(7);
        message.txCounter = packet.getUint8(8);
        message.txCost = packet.getUint8(9);
        message.rxLqi = packet.getUint8(10);
        singletons->getDeviceInfoDispatcher()->dispatch(&message);
    }
}