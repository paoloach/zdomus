//
// Created by paolo on 03/01/17.
//

#ifndef DOMUS_ENGINE_BINDTABLESERIALEXECUTER_H
#define DOMUS_ENGINE_BINDTABLESERIALEXECUTER_H

#include <boost/log/trivial.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"
#include "../ZigbeeData/ZDevices.h"
#include "../ZigbeeData/Exceptions/InvalidZDevice.h"

namespace zigbee {
    class BindTableSerialExecutor : public SerialExecutor {
    public:
        BindTableSerialExecutor(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        // BT:  extAddressSource, endpointIdSource, clusterId, networkIdDest, endpointIdDesc
        //       16 digits      ,      2digits    ,  4 digits,   4 digits   ,   2 digits
        virtual void operator()(const std::string &msg) override {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> > tok(msg, sep);
            auto tokIter = tok.begin();
            tokIter++;
            ExtAddress extAddress =  boost::lexical_cast<ExtAddress>(*tokIter);
            tokIter++;
            EndpointID endpointIdSrc{{std::stoi(*tokIter, nullptr, 16)}};
            tokIter++;
            ClusterID clusterId{{std::stoi(*tokIter, nullptr, 16)}};
            tokIter++;
            NwkAddr nwkAddrDst{std::stoi(*tokIter, nullptr, 16)};
            tokIter++;
            EndpointID endpointIdDst{*tokIter};
            try {
                ZDevice *device = singletons.getZDevices()->getDevice(extAddress);
                singletons.getBindTable().add(BindResponse(device->getNwkAddr(), endpointIdSrc, clusterId, nwkAddrDst, endpointIdDst));
            } catch (InvalidZDevice & e){
                BOOST_LOG_TRIVIAL(error) << "The device " << extAddress << " is not registered";
            }
        }
    private:
        SingletonObjectsImpl &singletons;
    };
}
#endif //DOMUS_ENGINE_BINDTABLESERIALEXECUTER_H
