//
// Created by paolo on 08/06/17.
//

#include <algorithm>
#include "AttributesResponseQueue.h"
#include "AttributeKey.h"
#include "ZigbeeDevice.h"

using std::vector;
using std::unique_ptr;

namespace zigbee {
    AttributesResponseQueue::Responses::Responses(vector<ZigbeeAttributeId> &attributesId,
                                                  unique_ptr<AttributesResponseCallback> &&callback) :
            callback(std::move(callback)) {
        notified.resize(attributesId.size());
        std::fill(notified.begin(), notified.begin(), false);
        attributes.resize(attributesId.size());
        std::fill(attributes.begin(), attributes.begin(), nullptr);
    }

    void AttributesResponseQueue::Responses::arrived(ZCLAttribute *attribute, int index) {
        notified[index] = true;
        attributes[index] = attribute;
        if (allNotified()){
            callback->response(std::move(attributes));
        }
    }

    void AttributesResponseQueue::Responses::timeout(int index) {
        notified[index] = true;
        if (allNotified()){
            callback->response(std::move(attributes));
        }
    }

    void AttributesResponseQueue::SingleAttrResponse::response(ZCLAttribute * attribute) {
        responses->arrived(attribute, index);
    }

    void AttributesResponseQueue::SingleAttrResponse::timeout() {
        responses->timeout(index);
    }

    void AttributesResponseQueue::add(AttributesKey key, std::unique_ptr<AttributesResponseCallback> &&callback) {
        auto responses = std::make_shared<Responses>(key.attributesId, std::move(callback));

        for(int index=0; index < key.attributesId.size(); index++){
            AttributeKey attributeKey{key.networkAddress, key.endpoint, key.clusterId, key.attributesId[index]};
            zigbeeDevice->registerForAttributeValue(attributeKey, std::make_unique<SingleAttrResponse>(index, responses));
        }

    }
}