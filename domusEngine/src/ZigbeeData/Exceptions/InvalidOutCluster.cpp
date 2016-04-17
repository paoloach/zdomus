//
// Created by paolo on 04/04/16.
//
#include <sstream>
#include "InvalidOutCluster.h"

zigbee::InvalidOutCluster::InvalidOutCluster(zigbee::NwkAddr nwkAddress, zigbee::EndpointID endpoint, zigbee::ClusterID wrongCluster) {
    std::stringstream stream{};
    stream << "The cluster " << wrongCluster << " doesn't exist in the output cluster list for endpoint " << endpoint << " on device " << nwkAddress << std::endl;
    message = stream.str();
}

