//
// Created by paolo on 07/01/17.
//

#ifndef DOMUS_ENGINE_DEVICEINFOSERIALEXECUTOR_H
#define DOMUS_ENGINE_DEVICEINFOSERIALEXECUTOR_H


#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <zigbee/NwkAddr.h>
#include "SerialExecutor.h"
#include "../usb/AttributeValuesSignalMap.h"
#include "../Utils/SingletonObjects.h"


namespace zigbee {
    class DeviceInfoSerialExecutor : public SerialExecutor {
    public:
        DeviceInfoSerialExecutor(SingletonObjects &singletons) : singletons(singletons) {}

// format: DI: network id, node relation, dev status, assoc count,   age   , txCounter, txCost  , rxLqi,
//             4 digits  ,   2 digits   , 2 digits  , 2 digits   , 2 digits, 2 digits , 2 digits, 2 digits
        virtual void operator()(const std::string &msg) override {
            DeviceInfoMessage message;
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> > tok(msg, sep);
            try {
                auto tokIter = tok.begin();
                tokIter++;
                message.nwkAddr = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.nodeRelation  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.devStatus  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.assocCnt  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.age  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.txCounter  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.txCost  = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                message.rxLqi  = std::stoi(*tokIter, nullptr, 16);
                singletons.getDeviceInfoDispatcher()->dispatch(&message);
            } catch (boost::bad_lexical_cast &e) {
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjects &singletons;
    };
}

#endif //DOMUS_ENGINE_DEVICEINFOSERIALEXECUTOR_H
