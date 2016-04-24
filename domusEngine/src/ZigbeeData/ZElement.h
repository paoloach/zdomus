//
// Created by paolo on 23/04/16.
//

#ifndef DOMUS_ENGINE_ZELEMENT_H
#define DOMUS_ENGINE_ZELEMENT_H

#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>


namespace  zigbee {

  class ZElement {
  public:
      ZElement(NwkAddr  address,EndpointID endpoint):address(address),endpoint(endpoint){}

      NwkAddr  address;
      EndpointID endpoint;

      bool operator<(const ZElement & other){
          return other.address == address ? other.endpoint < endpoint : other.address < address;
      }
  };
}


#endif //DOMUS_ENGINE_ZELEMENT_H
