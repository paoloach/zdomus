//
// Created by paolo on 22/04/16.
//

#ifndef DOMUS_ENGINE_BINDRESPONSE_H
#define DOMUS_ENGINE_BINDRESPONSE_H

#include <stdint.h>
#include <zigbee/zigbeeConfig.h>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zigbee/NwkAddr.h>
#include <array>
#include <vector>
#include <memory>

namespace zigbee {

  struct BindResponse {
      union shortConvert {
          shortConvert(uint8_t a, uint8_t b){
              raw[0] = a;
              raw[1] = b;
          }

          uint8_t raw[2];
          uint16_t value;
      };
  public:
      BindResponse(uint8_t * & data);
      NwkAddr srcAddr;
      EndpointID srcEP;
      ClusterID  clusterId;
      NwkAddr dstAddr;
      EndpointID dstEP;
  };

}


#endif //DOMUS_ENGINE_BINDRESPONSE_H
