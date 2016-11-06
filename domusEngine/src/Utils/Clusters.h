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


namespace zigbee {
    class ClusterTypeFactory;
    class ZigbeeDevice;
    class Cluster;

    class Clusters {
    public:
        Clusters(ZigbeeDevice* zigbeeDevice);
        Clusters()=default;
        virtual     std::shared_ptr<Cluster> getCluster(NwkAddr networkAddress, const EndpointID  endpoint,ClusterID clusterId);

    private:
        typedef std::tuple<NwkAddr, EndpointID, ClusterID> Key;

        std::shared_ptr<ClusterTypeFactory> clusterTypeFactory;
        ZigbeeDevice* zigbeeDevice;
        std::map<Key, std::shared_ptr<Cluster> > clusters;
    };
}


#endif //DOMUS_ENGINE_CLUSTERS_H
