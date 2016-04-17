//
// Created by paolo on 04/04/16.
//
#include <sstream>
#include "InvalidInCluster.h"

zigbee::InvalidInCluster::InvalidInCluster(zigbee::NwkAddr nwkAddress, zigbee::EndpointID endpoint, zigbee::ClusterID wrongCluster) {
    std::stringstream stream{};
    stream << "The cluster " << wrongCluster << " doesn't exist in the input cluster list of endpoint " << endpoint << " on device " << nwkAddress << std::endl;
    message = stream.str();
}
