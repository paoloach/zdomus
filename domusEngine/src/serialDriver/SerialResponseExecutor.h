//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_SERIALRESPONSEEXECUTOR_H
#define DOMUS_ENGINE_SERIALRESPONSEEXECUTOR_H

#include <string>
#include <map>
#include <memory>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"


namespace zigbee {
    class SerialResponseExecutor {

        enum class CmdType {
            Invalid, AnnunceDevice, IEEEAddress,
            IEEEAddressError, SimpleDescriptor, ActiveEndpointError,
            BindTableEntry, ReadAttributeError, ReadAttribute, DeviceInfo,
            PowerNode,PowerNodeError, Alive
        };

    public:
        SerialResponseExecutor(SingletonObjectsImpl &singletonObjects);

        void execute(const std::string &str);

    private:
        CmdType getResponseType(const std::string &str);

        std::map<CmdType, std::unique_ptr<SerialExecutor> > executors;

    };
}


#endif //DOMUS_ENGINE_SERIALRESPONSEEXECUTOR_H
