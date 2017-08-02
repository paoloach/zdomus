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
    class IEEEAddressResponseSerialExecutor : public SerialExecutor {
    public:
        IEEEAddressResponseSerialExecutor(SingletonObjects &singletonObjects) : singletonObjects(singletonObjects) {}

        // IE: ieeeaddress, networkAddress, numChild, firstChildNwkId, ..., lastChildNwkId
        //      16digits ,     4digits,      2digits,  4digits,      , ...,  4digits
        virtual void operator()(const std::string &msg) override {
            IEEEAddrResp message;
            try {
                boost::char_separator<char> sep(", ");
                boost::tokenizer<boost::char_separator<char> > tok(msg, sep);

                auto tokIter = tok.begin();
                tokIter++;
                if (tokIter.at_end()){
                    BOOST_LOG_TRIVIAL(error) << "Invalid message";
                    return;
                }
                message.ieeeAddr = boost::lexical_cast<ExtAddress>(*tokIter);
                tokIter++;
                if (tokIter.at_end()){
                    BOOST_LOG_TRIVIAL(error) << "Invalid message";
                    return;
                }
                message.nwkAddr = NwkAddr{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                if (tokIter.at_end()){
                    BOOST_LOG_TRIVIAL(error) << "Invalid message";
                    return;
                }
                int nChild = std::stoi(*tokIter, nullptr, 16);
                for (int i = 0; i < nChild; i++) {
                    tokIter++;
                    if (tokIter.at_end()){
                        BOOST_LOG_TRIVIAL(error) << "Invalid message";
                        return;
                    }
                    message.children.emplace(std::stoi(*tokIter, nullptr, 16));
                }
                singletonObjects.getZDevices()->addDeviceInfo(message);
            } catch (std::exception &e) {
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjects &singletonObjects;
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
