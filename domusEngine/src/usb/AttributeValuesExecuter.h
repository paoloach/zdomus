//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
#define DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H

#include <zcl/ClusterTypeFactory.h>
#include <zcl/ZclAttributeUtils.h>

#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/ReadAttributeResponseMessage.h>

namespace zigbee {
    class AttributeValuesExecuter : public Executor {
    private:
        SingletonObjects &singletonObjects;
    public:
        AttributeValuesExecuter(SingletonObjects &singletonObjects) : singletonObjects(singletonObjects) { }

        virtual void operator()(unsigned char *data, int) override {
            ReadAttributeResponseMessage *readAttributeResponseMessage = reinterpret_cast<ReadAttributeResponseMessage *>(data);
            BOOST_LOG_TRIVIAL(debug) << "Read " << readAttributeResponseMessage->numAttributes << " attribute value from " <<
                                     (int) readAttributeResponseMessage->networkAddr << ":" <<
                                     readAttributeResponseMessage->endpoint << ":" << (int) readAttributeResponseMessage->clusterId;
            uint8_t *rawResponses = data + sizeof(ReadAttributeResponseMessage);
            for (int i = 0; i < readAttributeResponseMessage->numAttributes; i++) {
                std::stringstream log;
                AttributeResponse *response = reinterpret_cast<AttributeResponse *>(rawResponses);
                uint8_t * rawData = rawResponses + sizeof(AttributeResponse);

                log << "Read attribute " << (int) response->attrID << ", status " << (int) response->status;

                size_t dataLen = ZclAttributeUtils::zclGetAttrDataLength(response->dataType, rawData);
                log << ", dataLen: " << dataLen;
                auto zigbeeDevice =singletonObjects.getZigbeeDevice();

                std::shared_ptr<Cluster> cluster{singletonObjects.getClusters()->getCluster(NwkAddr{readAttributeResponseMessage->networkAddr},
                                                                        EndpointID{readAttributeResponseMessage->endpoint},
                                                                        ClusterID{readAttributeResponseMessage->clusterId}
                                                                                  )};
                auto attribute = cluster->getAttribute(response->attrID);
                attribute->setValue(*response);

                auto attributeValueSignalMap = singletonObjects.getAttributeValueSignalMap();
                AttributeKey key(NwkAddr(readAttributeResponseMessage->networkAddr), readAttributeResponseMessage->endpoint,
                                 readAttributeResponseMessage->clusterId, response->attrID);
                if (attributeValueSignalMap.count(key) > 0) {
                    attributeValueSignalMap.execute(key, 0);
                }
                rawResponses += sizeof(AttributeResponse) + dataLen;
                BOOST_LOG_TRIVIAL(debug) << log.str();
            }
        }
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
