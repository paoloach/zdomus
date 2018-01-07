//
// Created by Paolo Achdjian on 11/18/15.
// Copyright (c) Paolo Achdjian All rights reserved.

//

#ifndef ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H
#define ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H


#include <string>
#include <memory>
#include "zcl/impl/ClusterImpl.h"

#include "../../zigbee/ZigbeeDevice.h"

namespace zigbee {


class ElectricalMeasurementCluster : public ClusterImpl {
public:
    ElectricalMeasurementCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID  endpoint, NwkAddr networkAddress);
public:
    ClusterID getId() const override;
    std::string getClusterName() const override;
};

}


#endif //ZIGBEE_LIB_ELECTRICALMEASURAMENTCLUSTER_H
