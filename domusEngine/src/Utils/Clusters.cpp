//
// Created by paolo on 09/06/16.
//

#include <zcl/ClusterTypeFactory.h>

#include "Clusters.h"


namespace zigbee {
    Clusters::Clusters(std::shared_ptr<ZigbeeDevice> zigbeeDevice) : clusterTypeFactory{std::make_shared<ClusterTypeFactory>()},
                                                                     zigbeeDevice{zigbeeDevice} {

    }

    std::shared_ptr<Cluster> Clusters::getCluster(NwkAddr networkAddress, const EndpointID endpoint, ClusterID clusterId) {

        auto key = std::make_tuple(networkAddress,endpoint, clusterId);
        auto found = clusters.find(key);
        if (found != clusters.end()){
            return found->second;
        }
        auto cluster = clusterTypeFactory->getCluster(clusterId, zigbeeDevice, endpoint, networkAddress);
        clusters.insert({key, cluster});
        return cluster;

    }


}
