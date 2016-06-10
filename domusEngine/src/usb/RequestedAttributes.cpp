//
// Created by paolo on 06/06/16.
//

#include "RequestedAttributes.h"

namespace zigbee {
    RequestedAttributes::RequestedAttributes(NwkAddr nwkAddrs, EndpointID endpoint, zigbee::ClusterID clusterID,
                                             const ZigbeeAttributeIds &attributeIds) {
        for (auto &&attributeId : attributeIds) {
            attributes.emplace_back(nwkAddrs, endpoint, clusterID, attributeId);
        }
    }

    bool RequestedAttributes::Attribute::operator<(const Attribute &attribute) const{
        if (nwkAddrs == attribute.nwkAddrs) {
            if (endpoint == attribute.endpoint){
                if (clusterID == attribute.clusterID){
                    return attributeId < attribute.attributeId;
                } else {
                    return clusterID < attribute.clusterID;
                }
            } else {
                return endpoint < attribute.endpoint;
            }
        } else {
            return nwkAddrs < attribute.nwkAddrs;
        }
    }
}

