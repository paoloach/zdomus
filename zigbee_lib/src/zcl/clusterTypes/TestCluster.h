//
// Created by Paolo Achdjian on 02/13/16.
// Copyright (c) Paolo Achdjian All rights reserved.
//

#ifndef ZIGBEE_LIB_TESTCLUSTER_H
#define ZIGBEE_LIB_TESTCLUSTER_H


#include <string>
#include <memory>
#include "../Cluster.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {


class TestCluster : public Cluster {
public:
    TestCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
    ClusterID getId() const override;
    std::string getClusterName() const override;
};

}


#endif //ZIGBEE_LIB_TESTCLUSTER_H
