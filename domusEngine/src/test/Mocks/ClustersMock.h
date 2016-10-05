//
// Created by paolo on 04/10/16.
//

#ifndef DOMUS_ENGINE_CLUSTERSMOCK_H
#define DOMUS_ENGINE_CLUSTERSMOCK_H


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../Utils/Clusters.h"

namespace zigbee {
    namespace test {
        class ClustersMock  : public Clusters {
        public:
            MOCK_METHOD3(getCluster, std::shared_ptr<Cluster> (NwkAddr networkAddress, const EndpointID  endpoint,ClusterID clusterId));
        };
    }
}


#endif //DOMUS_ENGINE_CLUSTERSMOCK_H
