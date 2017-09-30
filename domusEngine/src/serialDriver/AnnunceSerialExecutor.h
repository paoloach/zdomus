//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
#define DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H

#include <boost/log/trivial.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class AnnunceSerialExecutor : public SerialExecutor {
    public:
        AnnunceSerialExecutor(SingletonObjects &singletons) : singletons(singletons) {}

        // format: AN: networkId , extendAddress, capability
        virtual void operator()(const std::string &msg) override {
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
                singletons.getZigbeeDevice()->requestBindTable(nwkAddr);
            } catch (boost::bad_lexical_cast &e) {
                BOOST_LOG_TRIVIAL(error) << "Unable to decode Annunce message: " << e.what();
            }
        }

    private:
        SingletonObjects &singletons;
    };
}

#endif //DOMUS_ENGINE_ANNUNCESERIALEXECUTOR_H
