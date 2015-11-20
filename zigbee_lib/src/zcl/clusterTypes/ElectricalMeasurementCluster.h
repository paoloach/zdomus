//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H
#define ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H


#include <string>
#include <memory>
#include "../Cluster.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {


class ElectricalMeasurementCluster : public Cluster {
public:
    ElectricalMeasurementCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
    virtual ClusterID getId();
    virtual std::string getClusterName();
private:
    void getMeasurementProfileCommand(void(std::vector<uint8_t> && data));
};

}


#endif //ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H
