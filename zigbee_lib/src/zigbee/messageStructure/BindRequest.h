/*
 * BindRequest.h
 *
 *  Created on: 11/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_MESSAGESTRUCTURE_BINDREQUEST_H_
#define SRC_ZIGBEE_MESSAGESTRUCTURE_BINDREQUEST_H_

#include "ZAddrType.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"

namespace zigbee {

  struct __attribute__ ((__packed__)) BindRequest {
      BindRequest(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, uint8_t inClusterAddr[Z_EXTADDR_LEN],
                  EndpointID inClusterEp) noexcept : generticDataMsg(REQ_ADD_BIND_TABLE_ENTRY),
                                                     destAddr(destAddr.getId()), outClusterEP(outClusterEP.getId()), clusterID(clusterID.getId()),
                                                     inClusterEp(inClusterEp.getId()) {
          memcpy(this->outClusterAddr, outClusterAddr, Z_EXTADDR_LEN);
          memcpy(this->inClusterAddr, inClusterAddr, Z_EXTADDR_LEN);
      }

      GenericMessage generticDataMsg;
      uint16_t destAddr;
      uint8_t outClusterAddr[Z_EXTADDR_LEN];
      uint8_t outClusterEP;
      uint16_t clusterID;             // Cluster ID
      uint8_t inClusterAddr[Z_EXTADDR_LEN];
      uint8_t inClusterEp;
  };

} /* namespace zigbee */

#endif /* SRC_ZIGBEE_MESSAGESTRUCTURE_BINDREQUEST_H_ */
