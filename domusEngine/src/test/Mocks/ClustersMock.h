//
// Created by paolo on 04/10/16.
//

#ifndef DOMUS_ENGINE_CLUSTERSMOCK_H
#define DOMUS_ENGINE_CLUSTERSMOCK_H

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../Utils/Clusters.h"

namespace zigbee {
    namespace test {
        class ClustersMock  : public Clusters {
        public:
            MAKE_MOCK3(getCluster, Cluster * (NwkAddr networkAddress, const EndpointID  endpoint,ClusterID clusterId));
        };
    }
}


#endif //DOMUS_ENGINE_CLUSTERSMOCK_H
