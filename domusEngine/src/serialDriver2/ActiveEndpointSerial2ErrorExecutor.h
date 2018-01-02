//
// Created by paolo on 03/01/17.
//

#ifndef ACTIVE_ENDPOINT_SERIAL2_ERROR_EXECUTOR_H
#define ACTIVE_ENDPOINT_SERIAL2_ERROR_EXECUTOR_H
#include <boost/log/trivial.hpp>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjectsImpl.h"
namespace zigbee {
    class ActiveEndpointSerial2ErrorExecutor : public Serial2Executor {
    public:
        // format: AEE: networkId, status
        virtual void operator()(Packet &&packet ) override {
            NwkAddr nwkAddr(packet.getUint16(1));
            int cause = packet.getUint8(3);
            std::stringstream stream;
            stream << "error requesting acttive enpoint at " << nwkAddr << " because ";
            switch (cause){
                case 0x02:
                    stream << " invalid parameter";
                    break;
                case 0x10:
                    stream << " memory fail";
                    break;
                case 0xCD:
                    stream  << " no route";
                    break;
                default:
                    stream << " error code " << cause;
            }
            BOOST_LOG_TRIVIAL(error) <<stream.str();
        }
    };
}

#endif //ACTIVE_ENDPOINT_SERIAL2_ERROR_EXECUTOR_H
