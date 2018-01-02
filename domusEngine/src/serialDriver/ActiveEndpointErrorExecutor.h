//
// Created by paolo on 03/01/17.
//

#ifndef DOMUS_ENGINE_ACTIVEENDPOINTERROREXECUTOR_H
#define DOMUS_ENGINE_ACTIVEENDPOINTERROREXECUTOR_H
#include <boost/log/trivial.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"
namespace zigbee {
    class ActiveEndpointSerialErrorExecutor : public SerialExecutor {
    public:
        // format: AEE: networkId, status
        virtual void operator()(const std::string & msg ) override {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> >  tok(msg, sep);
            auto tokIter = tok.begin();
            tokIter++;
            NwkAddr nwkAddr(std::stoi(*tokIter, nullptr, 16));
            tokIter++;
            int cause = std::stoi(*tokIter, nullptr, 16);
            std::stringstream stream;
            stream << "error requesting acttive enpoint at " << nwkAddr << " because ";
            switch (cause){
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
                    stream << " error code " << cause;
            }
            BOOST_LOG_TRIVIAL(error) <<stream.str();
        }
    };
}

#endif //DOMUS_ENGINE_ACTIVEENDPOINTERROREXECUTOR_H
