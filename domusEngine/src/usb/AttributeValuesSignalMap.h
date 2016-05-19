//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUESSIGNALMAP_H
#define DOMUS_ENGINE_ATTRIBUTEVALUESSIGNALMAP_H

#include <zigbee/NwkAddr.h>
#include <zigbee/AttributeStatusRecord.h>
#include <zcl/ZCLDataType.h>

namespace zigbee {

    struct AttributeKey {
        AttributeKey(NwkAddr nwkAddress, ZigbeeEndpoint endpoint, ZigbeeClusterId cluster, ZigbeeAttributeId attributeId) :
                nwkAddr(nwkAddress), endpointId(endpoint), clusterId(cluster), attributeId(attributeId) {
        }

        NwkAddr nwkAddr;
        ZigbeeEndpoint endpointId;
        ZigbeeClusterId clusterId;
        ZigbeeAttributeId attributeId;

        bool operator<(const AttributeKey &otherKey) const;

        bool operator==(const AttributeKey &otherKey) const;
    };

    inline bool AttributeKey::operator<(const AttributeKey &otherKey) const {
        if (nwkAddr == otherKey.nwkAddr) {
            if (endpointId == otherKey.endpointId) {
                if (clusterId == otherKey.clusterId) {
                    return attributeId < otherKey.attributeId;
                } else {
                    return clusterId < otherKey.clusterId;
                }
            } else {
                return endpointId < otherKey.endpointId;
            }
        } else {
            return nwkAddr < otherKey.nwkAddr;
        }
    }

    inline bool AttributeKey::operator==(const AttributeKey &otherKey) const {
        return otherKey.nwkAddr == nwkAddr && otherKey.endpointId == endpointId && otherKey.clusterId == clusterId &&
               otherKey.attributeId == attributeId;
    }

    using NewAttributeValueCallback = std::function<void(int status)>;

    class AttributeValueSignalMap : public std::multimap<AttributeKey, NewAttributeValueCallback> {
    public:
        void execute(const AttributeKey &key, int status) {
            if (count(key) > 0) {
                for (auto iter = lower_bound(key); iter != upper_bound(key); iter++) {
                    iter->second(status);
                }
            }
        }
        void insert(const AttributeKey &key,const  NewAttributeValueCallback & fn){
            multimap::insert(value_type{key,fn});
        }
    };

}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESSIGNALMAP_H