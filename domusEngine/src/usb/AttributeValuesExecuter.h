//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
#define DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H

#include <zcl/ZclAttributeUtils.h>

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/ReadAttributeResponseMessage.h>

namespace zigbee {
    class AttributeValuesExecuter : public Executor {
    private:
        AttributeDataContainer &attributeDataContainer;
        AttributeValueSignalMap &attributeValueSignalMap;
    public:
        AttributeValuesExecuter(AttributeDataContainer &attributeDataContainer, AttributeValueSignalMap &attributeValueSignalMap)
                : attributeDataContainer(attributeDataContainer), attributeValueSignalMap(attributeValueSignalMap) { }

        virtual void operator()(unsigned char *data, int) override {
            ReadAttributeResponseMessage *readAttributeResponseMessage = reinterpret_cast<ReadAttributeResponseMessage *>(data);
            BOOST_LOG_TRIVIAL(debug) << "Read " << readAttributeResponseMessage->numAttributes << " attribute value from " <<
                        (int)readAttributeResponseMessage->networkAddr << ":" <<
                                     readAttributeResponseMessage->endpoint << ":" << (int)readAttributeResponseMessage->clusterId;
            uint8_t *rawResponses = data + sizeof(ReadAttributeResponseMessage);
            for (int i = 0; i < readAttributeResponseMessage->numAttributes; i++) {
                AttributeResponse *response = reinterpret_cast<AttributeResponse *>(rawResponses);

                BOOST_LOG_TRIVIAL(debug) << "Read attribute " << (int)response->attrID << ", status " << response->status;

                uint8_t *data = rawResponses + sizeof(AttributeResponse);

                size_t dataLen = ZclAttributeUtils::zclGetAttrDataLength(response->dataType, data);
                attributeDataContainer.push(AttributeData(*readAttributeResponseMessage, *response, dataLen));

                AttributeKey key(NwkAddr(readAttributeResponseMessage->networkAddr), readAttributeResponseMessage->endpoint,
                                 readAttributeResponseMessage->clusterId, response->attrID);
                if (attributeValueSignalMap.count(key) > 0) {
                    attributeValueSignalMap.execute(key, 0);
                }

                rawResponses += sizeof(AttributeResponse) + dataLen;
            }
        }
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
