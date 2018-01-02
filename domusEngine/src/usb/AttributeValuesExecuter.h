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
        SingletonObjectsImpl &singletonObjects;
    public:
        AttributeValuesExecuter(SingletonObjectsImpl &singletonObjects) : singletonObjects(singletonObjects) {}

        virtual void operator()(unsigned char *data, int) override {
            ReadAttributeResponseMessage *readAttributeResponseMessage = reinterpret_cast<ReadAttributeResponseMessage *>(data);
            BOOST_LOG_TRIVIAL(info) << "Read " << readAttributeResponseMessage->numAttributes << " attribute value from " << (int) readAttributeResponseMessage->networkAddr << ":"
                                    << readAttributeResponseMessage->endpoint << ":" << (int) readAttributeResponseMessage->clusterId;
            uint8_t *rawResponses = data + sizeof(ReadAttributeResponseMessage);
            for (int i = 0; i < readAttributeResponseMessage->numAttributes; i++) {
                std::stringstream log;
                std::stringstream rawLog;

                for (int i = 0; i < 30; i++) {
                    log << std::hex << (uint) (rawResponses[i]) << ",";
                }
                BOOST_LOG_TRIVIAL(debug) << log.str();
                AttributeResponse *response = reinterpret_cast<AttributeResponse *>(rawResponses);
                uint8_t *rawData = rawResponses + sizeof(AttributeResponse);
                size_t dataLen = ZclAttributeUtils::zclGetAttrDataLength(response->dataType, rawData);
                NwkAddr nwkAddr{readAttributeResponseMessage->networkAddr};
                EndpointID endpointID{readAttributeResponseMessage->endpoint};
                ClusterID clusterID{readAttributeResponseMessage->clusterId};
                AttributeKey key{nwkAddr, endpointID, clusterID, response->attrID};
                BOOST_LOG_TRIVIAL(debug) << "Read attribute " << key << " width status " << (int)response->status << " and data length " << dataLen;

                std::shared_ptr<Cluster> cluster{singletonObjects.getClusters()->getCluster(nwkAddr, endpointID, clusterID)};
                auto attribute = cluster->getAttribute(response->attrID);
                attribute->setValue(*response);

                rawResponses += sizeof(AttributeResponse) + dataLen;
                singletonObjects.getZigbeeDevice()->setAttribute(key,attribute);
            }
        }
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
