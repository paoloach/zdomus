//
// Created by paolo on 23/12/17.
//
#include <boost/log/trivial.hpp>
#include "../Utils/SingletonObjectsImpl.h"
#include "SimpleDescSerial2Executor.h"

namespace zigbee {
    void SimpleDescSerial2Executor::operator()(Packet &&packet) {
        NwkAddr nwkAddr{packet.getUint16(1)};
        EndpointID endpointId{packet.getUint8(3)};
        int profileId = packet.getUint16(4);
        int deviceId = packet.getUint16(6);
        int deviceVersion = packet.getUint8(8);
        int numInClusters = packet.getUint8(9);
        std::vector<ClusterID> inClusters;
        uint32_t index = 10;
        for (int i = 0; i < numInClusters; i++) {
            inClusters.emplace_back(packet.getUint16(index));
            index += 2;
        }
        int numOutClusters = packet.getUint8(index);
        index++;
        std::vector<ClusterID> outClusters;
        for (int i = 0; i < numOutClusters; i++) {
            outClusters.emplace_back(packet.getUint16(index));
            index += 2;
        }
        ZEndpoint zEndpoint(nwkAddr, endpointId, profileId, deviceId, deviceVersion, inClusters, outClusters);

        singletons.getZDevices()->put(zEndpoint);
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
    }
}