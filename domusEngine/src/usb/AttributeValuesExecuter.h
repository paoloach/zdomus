//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
#define DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H

#include <boost/log/trivial.hpp>

namespace zigbee {
    class AttributeValuesExecuter : public Executor {
    private:
        AttributeDataContainer &attributeDataContainer;
        AttributeValueSignalMap &attributeValueSignalMap;
    public:
        AttributeValuesExecuter(AttributeDataContainer &attributeDataContainer, AttributeValueSignalMap &attributeValueSignalMap)
                : attributeDataContainer(attributeDataContainer), attributeValueSignalMap(attributeValueSignalMap) { }

        virtual void operator()(unsigned char *data, int) override {
            BOOST_LOG_TRIVIAL(info) << "Read response attribute value";
            ReadAttributeResponseMessage *readAttributeResponseMessage = reinterpret_cast<ReadAttributeResponseMessage *>(data);
            AttributeKey key(NwkAddr(readAttributeResponseMessage->networkAddr), readAttributeResponseMessage->endpoint, readAttributeResponseMessage->clusterId, readAttributeResponseMessage->attrID);
            attributeDataContainer.push(*readAttributeResponseMessage);
            if (attributeValueSignalMap.count(key) > 0) {
                attributeValueSignalMap.execute(key, 0);
            }
        }
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
