//
// Created by paolo on 22/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODEREQERROR_H
#define DOMUS_ENGINE_POWERNODEREQERROR_H

#include <zigbee/messageStructure/ActiveEPErrorMessage.h>
#include <sstream>
#include <boost/log/trivial.hpp>
#include "Executor.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class PowerNodeReqError : public Executor {
    public:
        PowerNodeReqError(SingletonObjects * singletonObjects): singletonObjects(singletonObjects){}

        virtual void operator()(unsigned char *data, int) override {
            ActiveEPErrorMessage * errorMessage = reinterpret_cast<ActiveEPErrorMessage *>(data);
            int nwkAddr = errorMessage->nwkAddr;
            BOOST_LOG_TRIVIAL(error) <<"error requesting power node for device " << std::hex << nwkAddr << " because " << errorCodeToString(errorMessage->errorCode);
            auto powerNode = std::make_shared<PowerNodeData>(true);
            singletonObjects->getZigbeeDevice()->setPowerNode(powerNode);
        }
    private:
        SingletonObjects * singletonObjects;
    };
}
#endif //DOMUS_ENGINE_POWERNODEREQERROR_H
