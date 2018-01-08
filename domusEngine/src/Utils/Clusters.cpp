//
// Created by paolo on 09/06/16.
//

#include "Clusters.h"


namespace zigbee {

    Cluster * Clusters::getCluster(NwkAddr networkAddress, const EndpointID endpoint, ClusterID clusterId) {

        auto key = std::make_tuple(networkAddress,endpoint, clusterId);
        auto found = clusters.find(key);
        if (found != clusters.end()){
            return found->second.get();
        }
        clusters[key] = clusterTypeFactory.getCluster(clusterId, zigbeeDevice, endpoint, networkAddress);
        return clusters[key].get();
    }


}
