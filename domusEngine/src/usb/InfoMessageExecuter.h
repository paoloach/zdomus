//
// Created by paolo on 18/07/16.
//

#ifndef DOMUS_ENGINE_INFOMESSAGEEXECUTER_H
#define DOMUS_ENGINE_INFOMESSAGEEXECUTER_H


#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/InfoMessage.h>

namespace zigbee {
    class InfoMessageExecuter : public Executor {
    public:
        virtual void operator()(unsigned char *data, int len) override {
            InfoMessage *infoMessage = reinterpret_cast<InfoMessage *>(data);
            char * strData = reinterpret_cast<char *>(data + sizeof(InfoMessage));
            uint16_t  nwkAddr = infoMessage->nwkAddr;
            BOOST_LOG_TRIVIAL(info) << "from device " << std::dec<< nwkAddr << ": " << strData;
        }

    };
}

#endif //DOMUS_ENGINE_INFOMESSAGEEXECUTER_H
