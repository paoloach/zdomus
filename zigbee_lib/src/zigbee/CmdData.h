//
// Created by paolo on 24/08/17.
//

#ifndef ZIGBEE_LIB_CMDDATA_H
#define ZIGBEE_LIB_CMDDATA_H

#include <stdint.h>
#include "ZigbeeTypes.h"
#include "NwkAddr.h"
#include "EndpointID.h"
#include "ClusterID.h"

namespace zigbee {

    class CmdData {
    public:
        NwkAddr nwkAddrs;
        EndpointID endpoint;
        ClusterID cluster;
        ZigbeeClusterCmdId commandId;
        std::vector<uint8_t> data;

        CmdData(NwkAddr addr, const EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId command, std::vector<uint8_t> && data) :
                nwkAddrs{addr}, endpoint{endpoint}, cluster{cluster}, commandId{command}, data{std::move(data)} {

        }

        bool operator==(const CmdData &other) const {
            return nwkAddrs == other.nwkAddrs && endpoint == other.endpoint && cluster == other.cluster &&
                   commandId == other.commandId;
        };

        bool operator<(const CmdData &other) const {
            if (nwkAddrs == other.nwkAddrs) {
                if (endpoint == other.endpoint) {
                    if (cluster == other.cluster) {
                        return commandId < other.commandId;
                    } else {
                        return cluster < other.cluster;
                    }
                } else {
                    return endpoint < other.endpoint;
                }
            } else {
                return nwkAddrs < other.nwkAddrs;
            }
        }
    };

}
#endif //ZIGBEE_LIB_CMDDATA_H
