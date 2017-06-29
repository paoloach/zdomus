//
// Created by paolo on 04/06/17.
//

#ifndef ZIGBEE_LIB_ATTRIBUTEKEY_H
#define ZIGBEE_LIB_ATTRIBUTEKEY_H

#include <ostream>
#include "ClusterID.h"
#include "EndpointID.h"
#include "NwkAddr.h"


namespace zigbee {
    class AttributeKey {
    public:
        AttributeKey(NwkAddr networkAddress,EndpointID endpoint, ClusterID clusterId, ZigbeeAttributeId attributeId):
                attributeId(attributeId), clusterId(clusterId),endpoint(endpoint),networkAddress(networkAddress){}
        ZigbeeAttributeId attributeId;
        ClusterID clusterId;
        EndpointID endpoint;
        NwkAddr networkAddress;

        bool operator==(const AttributeKey & other) const;
        bool  operator < (const AttributeKey & other) const;

        friend std::ostream & operator<<(std::ostream & out, const AttributeKey & key){
            out << "{" << key.networkAddress << "," << key.endpoint << "," << key.clusterId << "," << key.attributeId << "}";
            return out;
        }
    };
}


#endif //ZIGBEE_LIB_ATTRIBUTEKEY_H
