//
// Created by paolo on 23/12/17.
//

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>
#include <boost/tokenizer.hpp>
#include "AnnunceSerialExecutor.h"
#include "../ZigbeeData/ExtAddress.h"
#include "../ZigbeeData/ZDevices.h"

namespace  zigbee {
// format: AN: networkId , extendAddress, capability
    void AnnunceSerialExecutor::operator()(const std::string &msg) {
        BOOST_LOG_NAMED_SCOPE("Annunce device");
        AnnunceMessage annunceMessage;
        boost::char_separator<char> sep(", ");
        boost::tokenizer<boost::char_separator<char> > tok(msg, sep);

        auto tokIter = tok.begin();
        try {
            tokIter++;
            annunceMessage.nwkAddr = std::stoi(*tokIter, nullptr, 16);
            tokIter++;

            ExtAddress extAddress = boost::lexical_cast<ExtAddress>(*tokIter);

            for (int i = 0; i < Z_EXTADDR_LEN; i++)
                annunceMessage.extAddr[i] = extAddress.getNible(i);
            tokIter++;
            annunceMessage.capabilities = std::stoi(*tokIter, nullptr, 16);
            singletons.getZDevices()->put(annunceMessage);

            NwkAddr nwkAddr{annunceMessage.nwkAddr};
            BOOST_LOG_TRIVIAL(info) << "Request endopoint";
            singletons.getZigbeeDevice()->requestActiveEndpoints(nwkAddr);
            sleep(1);
            BOOST_LOG_TRIVIAL(info) << "Request bind table";
            //singletons.getZigbeeDevice()->requestBindTable(nwkAddr);
        } catch (boost::bad_lexical_cast &e) {
            BOOST_LOG_TRIVIAL(error) << "Unable to decode Annunce message: " << e.what();
        }
    }

}