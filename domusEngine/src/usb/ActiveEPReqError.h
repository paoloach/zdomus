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
            std::stringstream stream;
            stream << "error requesting acttive enpoint at " << std::hex << nwkAddr << " because ";
            switch (activeEPErrorMessage->errorCode){
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
                    stream << " error code " << activeEPErrorMessage->errorCode;
            }
            BOOST_LOG_TRIVIAL(error) <<stream.str();
        }
    };
}
#endif //DOMUS_ENGINE_ACTIVEEPREQERROR_H
