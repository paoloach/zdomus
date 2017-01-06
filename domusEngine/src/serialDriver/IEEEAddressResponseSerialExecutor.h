//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/IEEEAddressResponse.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    class IEEEAddressResponseSerialExecutor : public SerialExecutor{
    public:
        IEEEAddressResponseSerialExecutor(SingletonObjects & singletonObjects):singletonObjects(singletonObjects){}

        // IE: ieeeaddress, networkAddress, numChild, firstChildNwkId, ..., lastChildNwkId
        //      16digits ,     4digits,      2digits,  4digits,      , ...,  4digits
        virtual void operator()(const std::string & msg) override {
            IEEEAddrResp message;
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> >  tok(msg, sep);
            try {
                auto tokIter = tok.begin();
                tokIter++;
                message.ieeeAddr = boost::lexical_cast<ExtAddress>(*tokIter);
                tokIter++;
                message.nwkAddr = NwkAddr{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                int nChild = std::stoi(*tokIter, nullptr, 16);
                for (int i = 0; i < nChild; i++) {
                    tokIter++;
                    message.children.emplace(std::stoi(*tokIter, nullptr,16));
                }
                singletonObjects.getZDevices()->addDeviceInfo(message);
            } catch (boost::bad_lexical_cast & e){
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjects & singletonObjects;
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
