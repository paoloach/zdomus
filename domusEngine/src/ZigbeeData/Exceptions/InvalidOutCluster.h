//
// Created by paolo on 04/04/16.
//

#ifndef DOMUS_ENGINE_INVALIDOUTCLUSTER_H
#define DOMUS_ENGINE_INVALIDOUTCLUSTER_H

#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>

#include "ZigbeeDeviceException.h"
namespace zigbee {
  class InvalidOutCluster  : public ZigbeeDeviceException {
  public:
      InvalidOutCluster(NwkAddr nwkAddress,EndpointID endpoint, ClusterID wrongCluster);
      virtual ~InvalidOutCluster()=default;
  };
}


#endif //DOMUS_ENGINE_INVALIDOUTCLUSTER_H
