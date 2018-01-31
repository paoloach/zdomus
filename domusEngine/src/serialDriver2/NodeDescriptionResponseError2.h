//
// Created by paolo on 30/01/18.
//

#ifndef DOMUS_ENGINE_NODEDESCRIPTIONRESPONSEERROR2_H
#define DOMUS_ENGINE_NODEDESCRIPTIONRESPONSEERROR2_H

#include "Serial2Executor.h"
#include <boost/log/trivial.hpp>
namespace zigbee {
    class NodeDescriptionResponseError2: public Serial2Executor {
    public:
        NodeDescriptionResponseError2() {}

        void operator()(Packet && packet) override{
            BOOST_LOG_TRIVIAL(error) << "Error requesting the Node Descriptor for network address " << packet.getUint16(1);
        }
    };
}


#endif //DOMUS_ENGINE_NODEDESCRIPTIONRESPONSEERROR2_H
