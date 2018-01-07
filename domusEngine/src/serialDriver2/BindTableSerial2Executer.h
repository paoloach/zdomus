//
// Created by paolo on 03/01/17.
//

#ifndef DOMUS_ENGINE_BINDTABLESERIAL2EXECUTER_H
#define DOMUS_ENGINE_BINDTABLESERIAL2EXECUTER_H

#include <boost/log/trivial.hpp>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/ZDevices.h"
#include "../ZigbeeData/Exceptions/InvalidZDevice.h"

namespace zigbee {
    class BindTableSerial2Executor : public Serial2Executor {
    public:
        BindTableSerial2Executor(SingletonObjects * singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet ) override {
            ExtAddress extAddress{packet.getExtAddress(1)};
            EndpointID endpointIdSrc{packet.getUint8(9)};
            ClusterID clusterId{packet.getUint16(10)};
            NwkAddr nwkAddrDst{packet.getUint16(12)};
            EndpointID endpointIdDst{packet.getUint8(14)};
            try {
                ZDevice *device = singletons->getZDevices()->getDevice(extAddress);
                singletons->getBindTable()->add(BindResponse(device->getNwkAddr(), endpointIdSrc, clusterId, nwkAddrDst, endpointIdDst));
            } catch (InvalidZDevice & e){
                BOOST_LOG_TRIVIAL(error) << "The device " << extAddress << " is not registered";
            }
        }
    private:
        SingletonObjects * singletons;
    };
}
#endif //DOMUS_ENGINE_BINDTABLESERIAL2EXECUTER_H
