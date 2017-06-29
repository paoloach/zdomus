//
// Created by paolo on 04/06/17.
//

#include "AttributeKey.h"

namespace  zigbee {
    bool AttributeKey::operator==(const AttributeKey &other) const {
        return networkAddress == other.networkAddress && endpoint == other.endpoint && clusterId == other.clusterId &&
               attributeId == other.attributeId;
    }

    bool AttributeKey::operator<(const AttributeKey &other) const{
        if (networkAddress == other.networkAddress) {
            if (endpoint == other.endpoint) {
                if (clusterId == other.clusterId) {
                    return attributeId < other.attributeId;
                } else {
                    return clusterId < other.clusterId;
                }
            } else {
                return endpoint < other.endpoint;
            }
        } else {
            return networkAddress < other.networkAddress;
        }
    }
}