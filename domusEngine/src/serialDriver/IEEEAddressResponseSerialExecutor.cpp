//
// Created by paolo on 17/01/18.
//
#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "../Utils/SingletonObjects.h"
#include "IEEEAddressResponseSerialExecutor.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {

    // IE: ieeeaddress, networkAddress, numChild, firstChildNwkId, ..., lastChildNwkId
    //      16digits ,     4digits,      2digits,  4digits,      , ...,  4digits
    void IEEEAddressResponseSerialExecutor::operator()(const std::string &msg) {
        BOOST_LOG_NAMED_SCOPE("serial driver");
        auto message = std::make_shared<IEEEAddressResponse>();
        try {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> > tok(msg, sep);

            auto tokIter = tok.begin();
            tokIter++;
            if (tokIter.at_end()){
                BOOST_LOG_TRIVIAL(error) << "Invalid message";
                return;
            }
            message->ieeeAddr = boost::lexical_cast<ExtAddress>(*tokIter);
            tokIter++;
            if (tokIter.at_end()){
                BOOST_LOG_TRIVIAL(error) << "Invalid message";
                return;
            }
            message->nwkAddr = NwkAddr{std::stoi(*tokIter, nullptr, 16)};
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
                message->children.emplace(std::stoi(*tokIter, nullptr, 16));
            }
            singletonObjects->getZDevices()->addDeviceInfo(message.get());
        } catch (std::exception &e) {
            BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
        }
    }
}
