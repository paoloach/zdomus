//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_SERIAL2RESPONSEEXECUTOR_H
#define DOMUS_ENGINE_SERIAL2RESPONSEEXECUTOR_H

#include <string>
#include <map>
#include <memory>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjects.h"
#include "Packet.h"

namespace zigbee {
    class Serial2ResponseExecutor {

        enum class CmdType {
            Invalid=0,
            STRING=1,
            Alive=2,
            DeviceInfo=3,
            ActiveEndpointError=4,
            ReadAttributeError=5,
            ReadAttribute=6,
            AnnunceDevice=7,
            PowerNodeError=8,
            PowerNode=9,
            SimpleDescriptor=10,
            IEEEAddress=11,
            IEEEAddressError=12,
            BindTableEntry=13,
            WriteAttributeError=14,
            NodeDescriptionError=15,
            NodeDescription=16,
            MgmtLqi=17,
            MgmtLqiNotSupported=18

        };


    public:
        Serial2ResponseExecutor(SingletonObjects * singletonObjects);

        void execute(Packet &&str);

    private:

        std::map<CmdType, std::unique_ptr<Serial2Executor> > executors;

    };
}


#endif //DOMUS_ENGINE_SERIALRESPONSEEXECUTOR_H
