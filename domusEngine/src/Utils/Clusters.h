//
// Created by paolo on 09/06/16.
//

#ifndef DOMUS_ENGINE_CLUSTERS_H
#define DOMUS_ENGINE_CLUSTERS_H

#include <memory>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <map>
#include <tuple>
#include <zcl/ClusterTypeFactory.h>

namespace zigbee {
    class ClusterTypeFactory;
    class ZigbeeDevice;
    class Cluster;

    class Clusters {
    public:
        Clusters(ZigbeeDevice* zigbeeDevice): zigbeeDevice{zigbeeDevice} {}
        Clusters()=default;
        virtual     Cluster *  getCluster(NwkAddr networkAddress, const EndpointID  endpoint,ClusterID clusterId);

    private:
        typedef std::tuple<NwkAddr, EndpointID, ClusterID> Key;

        ClusterTypeFactory clusterTypeFactory;
        ZigbeeDevice* zigbeeDevice;
        std::map<Key, std::unique_ptr<Cluster> > clusters;
    };
}


#endif //DOMUS_ENGINE_CLUSTERS_H
