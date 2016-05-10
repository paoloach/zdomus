//
// Created by paolo on 09/05/16.
//

#ifndef ZIGBEE_LIB_READATTRIBUTERESPONSEERRORMSG_H
#define ZIGBEE_LIB_READATTRIBUTERESPONSEERRORMSG_H

#include <ostream>
#include <stdint.h>
#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"

namespace zigbee {
    struct __attribute__ ((__packed__)) ReadAttributeResponseErrorMsg {
        ReadAttributeResponseErrorMsg(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId,
                       ZigbeeAttributeId attribute) noexcept:
                generticDataMsg{REQ_ATTRIBUTE_VALUES}, nwkAddr{nwkAddr.getId()}, endpoint{endpointId.getId()},
                cluster{clusterId.getId()}, attribute{attribute} {

        }

        ReadAttributeResponseErrorMsg() : nwkAddr(0), endpoint(0), cluster(0), attribute(0), status(0) {
            generticDataMsg.msgCode = REQ_ATTRIBUTE_VALUES;
        }

        GenericMessage generticDataMsg;
        ZigbeeNwkAddress nwkAddr;
        ZigbeeEndpoint endpoint;
        ZigbeeClusterId cluster;
        ZigbeeAttributeId attribute;
        uint8_t status;

    };

    inline std::ostream & operator<<(  std::ostream &out,  const ReadAttributeResponseErrorMsg &attribute ){
        out << "{" << attribute.nwkAddr << ":" << attribute.endpoint << ":" << attribute.cluster << ":" << attribute.attribute <<  " status: " << attribute.status;
        return out;
    }

}

#endif //ZIGBEE_LIB_READATTRIBUTERESPONSEERRORMSG_H
