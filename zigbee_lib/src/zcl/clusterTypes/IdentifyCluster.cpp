/*
 * IdentifyCluster.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/bind.hpp>
#include <iostream>

#include "IdentifyCluster.h"


namespace zigbee {

    static std::vector<Cluster::AttributeDef> attributesDef{
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 0, "Identify time")
    };


    IdentifyCluster::IdentifyCluster(ZigbeeDevice *zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress)
            : Cluster(zigbeeDevice, endpoint, networkAddress) {
        createAttributes(attributesDef);

        _commandsDef.emplace_back(
                [=](std::vector<uint8_t> &&) { zigbeeDevice->sendCmd(networkAddress, endpoint, IdentifyClusetrID, 0); },
                0, "Identify Command");
        _commandsDef.emplace_back(
                [=](std::vector<uint8_t> &&) { zigbeeDevice->sendCmd(networkAddress, endpoint, IdentifyClusetrID, 1); },
                1, "Identify Query Command");
    }

    ClusterID IdentifyCluster::getId() const {
        return IdentifyClusetrID;
    }

    std::string IdentifyCluster::getClusterName() const {
        return "identify";
    }

} /* namespace zigbee */
