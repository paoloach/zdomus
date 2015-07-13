/*
 * ClusterMock.cpp
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ClusterMock.h"

namespace zigbee {
namespace test {

ClusterMock::ClusterMock(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, EndpointID endpoint, NwkAddr networkAddress) :Cluster(zigbeeDevice,endpoint, networkAddress){

}


ClusterMock::ClusterMock() :Cluster(nullptr,EndpointID(), NwkAddr{}){

}

ClusterMock::~ClusterMock() {
}

} /* namespace test */
} /* namespace zigbee */
