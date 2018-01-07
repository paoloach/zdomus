//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_SIMPLEDESCSERIALEXECUTOR_H
#define DOMUS_ENGINE_SIMPLEDESCSERIALEXECUTOR_H


#include <boost/log/trivial.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    class SimpleDescSerialExecutor : public SerialExecutor {
    public:
        SimpleDescSerialExecutor(SingletonObjects * singletons) : singletons(singletons) {}

        // SD: networkID, endpoint, AppProfId, deviceId, deviceVersion, numInClusters, firstInCluster, ..., lastInCluster, numOutClusters, firstOutCluster, ..., lastOutCluster
        virtual void operator()(const std::string &msg) override {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> >  tok(msg, sep);
            try {
                auto tokIter = tok.begin();
                tokIter++;
                NwkAddr nwkAddr{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                EndpointID endpointId{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                int profileId = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                int deviceId = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                int deviceVersion = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                int numInClusters = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                std::vector<ClusterID> inClusters;
                for (int i = 0; i < numInClusters; i++) {
                    inClusters.emplace_back(std::stoi(*tokIter, nullptr, 16));
                    tokIter++;
                }
                int numOutClusters = std::stoi(*tokIter, nullptr, 16);
                tokIter++;
                std::vector<ClusterID> outClusters;
                for (int i = 0; i < numOutClusters; i++) {
                    outClusters.emplace_back(std::stoi(*tokIter, nullptr, 16));
                    tokIter++;
                }
                ZEndpoint zEndpoint(nwkAddr, endpointId, profileId, deviceId, deviceVersion, inClusters, outClusters);

                singletons->getZDevices()->put(zEndpoint);
                std::stringstream stream;
                stream << "Simple desciption message: {nwkAddr: " << nwkAddr << ", endpoint: " << endpointId << ", ";
                stream << "In Clusters {";
                for (auto &cluster: inClusters) {
                    stream << cluster << " ";
                }
                stream << "}, Out Cluster {";
                for (auto &cluster: outClusters) {
                    stream << cluster << " ";
                }
                stream << "} }";
                BOOST_LOG_TRIVIAL(info) << stream.str();
            } catch (boost::bad_lexical_cast &e ){
                BOOST_LOG_TRIVIAL(error) << "problem decoding Simple Descriptor message: cannot conver " <<e.what() << " into " << e.target_type().name();
            }
        }
    private:
        SingletonObjects* singletons;
    };
}


#endif //DOMUS_ENGINE_SIMPLEDESCSERIALEXECUTOR_H
