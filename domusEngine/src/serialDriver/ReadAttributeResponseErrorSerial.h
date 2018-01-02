//
// Created by paolo on 03/01/17.
//

#ifndef DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL_H
#define DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL_H
#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zcl/Cluster.h>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjectsImpl.h"

namespace zigbee {
    class ReadAttributeResponseErrorSerial : public SerialExecutor {
    public:
        ReadAttributeResponseErrorSerial(SingletonObjectsImpl & singletons):singletons(singletons) {}

        // format: RAE: networkId, endpointId, clusterId, attributeId, status
        //              4digits  ,  2digits  , 4 digits ,   4 digits , 2 digits
        virtual void operator()(const std::string &msg) override {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> >  tok(msg, sep);
            try {
                auto tokIter = tok.begin();
                tokIter++;
                NwkAddr nwkAddr{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                int endpointID{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                ZigbeeClusterId clusterId{static_cast<uint16_t >(std::stoi(*tokIter, nullptr, 16))};
                tokIter++;
                ZigbeeAttributeId attribute{static_cast<uint16_t >(std::stoi(*tokIter, nullptr, 16))};
                tokIter++;
                int status{std::stoi(*tokIter, nullptr, 16)};
                BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster="<< clusterId << ", attribute="<< attribute << ", cause: " << status;
                AttributeKey key(nwkAddr, EndpointID(endpointID), ClusterID(clusterId),attribute);
                auto cluster = singletons.getClusters()->getCluster(key.networkAddress, key.endpoint, key.clusterId);
                cluster->getAttribute(key.attributeId);
                singletons.getZigbeeDevice()->setAttribute(key,cluster->getAttribute(key.attributeId) );
            } catch (boost::bad_lexical_cast & e){
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjectsImpl & singletons;
    };
}
#endif //DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL_H
