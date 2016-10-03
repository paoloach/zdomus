//
// Created by paolo on 22/04/16.
//

#ifndef DOMUS_ENGINE_BINDRESPONSE_H
#define DOMUS_ENGINE_BINDRESPONSE_H

#include <cstdint>
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
            shortConvert(uint8_t a, uint8_t b) {
                raw[0] = a;
                raw[1] = b;
            }

            uint8_t raw[2];
            uint16_t value;
        };

    public:
        BindResponse(uint8_t *&data);

        BindResponse(NwkAddr srcAdd, EndpointID srcEndpoint, ClusterID clusterId, NwkAddr dstAddr,
                     EndpointID dstEndpoint) : srcAddr(srcAdd), srcEP(srcEndpoint), clusterId(clusterId),
                                               dstAddr(dstAddr), dstEP(dstEndpoint) { }

        NwkAddr srcAddr;
        EndpointID srcEP;
        ClusterID clusterId;
        NwkAddr dstAddr;
        EndpointID dstEP;
    };

}


#endif //DOMUS_ENGINE_BINDRESPONSE_H
