//
// Created by paolo on 14/06/16.
//

#ifndef DOMUS_ENGINE_ACTIVEEPREQERROR_H
#define DOMUS_ENGINE_ACTIVEEPREQERROR_H

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/ActiveEPErrorMessage.h>

#include "Executor.h"


namespace zigbee {
    class ActiveEPReqError : public Executor {
    public:
        virtual void operator()(unsigned char *data, int) override {
            ActiveEPErrorMessage * activeEPErrorMessage = reinterpret_cast<ActiveEPErrorMessage *>(data);
            int nwkAddr = activeEPErrorMessage->nwkAddr;
            BOOST_LOG_TRIVIAL(error) <<"error requesting power node for device " << std::hex << nwkAddr << " because " << errorCodeToString(activeEPErrorMessage->errorCode);
        }
    };
}
#endif //DOMUS_ENGINE_ACTIVEEPREQERROR_H
