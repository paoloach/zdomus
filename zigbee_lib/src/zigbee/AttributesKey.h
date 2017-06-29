//
// Created by paolo on 08/06/17.
//

#ifndef ZIGBEE_LIB_ATTRIBUTESKEY_H
#define ZIGBEE_LIB_ATTRIBUTESKEY_H

#include <ostream>
#include <vector>
#include "ClusterID.h"
#include "EndpointID.h"
#include "NwkAddr.h"

namespace zigbee {
    class AttributesKey {
    public:
        AttributesKey(){}
        AttributesKey(NwkAddr networkAddress, EndpointID endpoint, ClusterID clusterId,
                      std::vector<ZigbeeAttributeId> &&attributesId) :
                attributesId{std::move(attributesId)}, clusterId{clusterId}, endpoint{endpoint},
                networkAddress{networkAddress} {}

        AttributesKey(NwkAddr networkAddress, EndpointID endpoint, ClusterID clusterId,
                      std::vector<ZigbeeAttributeId> &attributesId) :
                attributesId{attributesId}, clusterId{clusterId}, endpoint{endpoint}, networkAddress{networkAddress} {}

        AttributesKey(AttributesKey  && other):
                    attributesId(std::move(other.attributesId)),
                    clusterId(other.clusterId),
                    endpoint(other.endpoint),
                    networkAddress(other.networkAddress){}

        AttributesKey(const AttributesKey  & other):
                attributesId(other.attributesId),
                clusterId(other.clusterId),
                endpoint(other.endpoint),
                networkAddress(other.networkAddress){}

        std::vector<ZigbeeAttributeId> attributesId;
        ClusterID clusterId;
        EndpointID endpoint;
        NwkAddr networkAddress;

        bool operator==(const AttributesKey &other) const;

        bool operator<(const AttributesKey &other) const;

        friend std::ostream &operator<<(std::ostream &out, const AttributesKey &key);
    };
}


#endif //ZIGBEE_LIB_ATTRIBUTESKEY_H
