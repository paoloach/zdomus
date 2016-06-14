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
    private:
        SingletonObjects &singletonObjects;
    public:
        ActiveEPReqError(SingletonObjects & singletonObjects):singletonObjects{singletonObjects}{}

        virtual void operator()(unsigned char *data, int) override {
            ActiveEPErrorMessage * activeEPErrorMessage = reinterpret_cast<ActiveEPErrorMessage *>(data);
            BOOST_LOG_TRIVIAL(error) << "error requesting acttive enpoint at " << activeEPErrorMessage->nwkAddr << " with error code: " << (int)activeEPErrorMessage->errorCode;
        }
    };
}
#endif //DOMUS_ENGINE_ACTIVEEPREQERROR_H
