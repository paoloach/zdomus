//
// Created by paolo on 04/04/16.
//

#ifndef DOMUS_ENGINE_INVALIDINCLUSTER_H
#define DOMUS_ENGINE_INVALIDINCLUSTER_H


#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>

#include "ZigbeeDeviceException.h"
namespace zigbee {
  class InvalidInCluster  : public ZigbeeDeviceException {
  public:
      InvalidInCluster(NwkAddr nwkAddress,EndpointID endpoint, ClusterID wrongCluster);
      virtual ~InvalidInCluster()=default;
  };
}

#endif //DOMUS_ENGINE_INVALIDINCLUSTER_H
