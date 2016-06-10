//
// Created by paolo on 06/06/16.
//

#ifndef DOMUS_ENGINE_REQUESTEDATTRIBUTES_H
#define DOMUS_ENGINE_REQUESTEDATTRIBUTES_H


#include <zigbee/ZigbeeTypes.h>
#include <zigbee/ClusterID.h>
#include <vector>
#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>

namespace zigbee {
    class RequestedAttributes {
    public:
        class Attribute {
        public:
            Attribute(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attribute) : nwkAddrs(
                    nwkAddrs), endpoint(endpoint), clusterID(cluster), attributeId(attribute) { }

            NwkAddr nwkAddrs;
            EndpointID endpoint;
            ClusterID clusterID;
            ZigbeeAttributeId attributeId;

            bool operator==(const Attribute &attribute) {
                return nwkAddrs == attribute.nwkAddrs && endpoint == attribute.endpoint &&
                       clusterID == attribute.clusterID && attributeId == attribute.attributeId;
            }

            bool operator<(const Attribute &attribute) const;
        };

        RequestedAttributes() { }

        RequestedAttributes(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID clusterID,
                            const ZigbeeAttributeIds &attributeIds);

        bool empty() { return attributes.empty(); }

        std::vector<Attribute> attributes;


    };
}


#endif //DOMUS_ENGINE_REQUESTEDATTRIBUTES_H
