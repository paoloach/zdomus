//
// Created by paolo on 04/01/17.
//

#ifndef DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL_H
#define DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL_H

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zcl/Cluster.h>
#include <zcl/ZCLAttribute.h>
#include <zcl/StatusEnum.h>
#include "SerialExecutor.h"
#include "../Utils/SingletonObjects.h"
#include "../Utils/Clusters.h"

namespace zigbee {
    class ReadAttributeResponseSerial : public SerialExecutor {
    public:
        ReadAttributeResponseSerial(SingletonObjects * singletons) : singletons(singletons) {}

        // format: RA: networkId, endpointId, clusterId, attributeId, attributeStatus,  attributeType,  attributeVelueLen, attributeValue
        //              4digits  ,  2digits  , 4 digits , 4 digits  ,    2  digits   ,    2 digits   ,    2 digits       ,   2* n digits where n =  attributeVelueLen
        //  attributeType, attributeVelueLen, attributeValue only if attributeStatus == 0
        virtual void operator()(const std::string &msg) override {
            boost::char_separator<char> sep(", ");
            boost::tokenizer<boost::char_separator<char> > tok(msg, sep);
            try {
                auto tokIter = tok.begin();
                tokIter++;
                NwkAddr nwkAddr{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                EndpointID endpointId{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                ClusterID clusterId{std::stoi(*tokIter, nullptr, 16)};
                tokIter++;
                ZigbeeAttributeId attributeId{static_cast<uint16_t >(std::stoi(*tokIter, nullptr, 16))};

                AttributeKey key{nwkAddr, endpointId, clusterId, attributeId};

                tokIter++;
                uint8_t status{static_cast<uint8_t >(std::stoi(*tokIter, nullptr, 16))};
                if (status == 0) {
                    tokIter++;
                    uint8_t attributeType{static_cast<uint8_t >(std::stoi(*tokIter, nullptr, 16))};
                    tokIter++;
                    uint8_t attributeLen{static_cast<uint8_t >(std::stoi(*tokIter, nullptr, 16))};
                    tokIter++;
                    Clusters *clusters = singletons->getClusters();
                    auto cluster = clusters->getCluster(nwkAddr, endpointId, clusterId);
                    Cluster *pCluster = cluster.get();
                    auto attribute = pCluster->getAttribute(attributeId);
                    if (attribute != nullptr) {
                        std::string rawData = *tokIter;
                        if (attributeLen * 2 == rawData.size()) {
                            uint8_t data[256];
                            for (int i = 0; i < attributeLen; i++) {
                                data[i] = std::stoi(rawData.substr(2 * i, 2), nullptr, 16);
                            }

                            attribute->setValue(status, attributeType, data);

                            BOOST_LOG_TRIVIAL(info) << "arrived attribute from  network id=" << nwkAddr << ", endpoint=" << endpointId << ", cluster=" << clusterId
                                                    << ", attribute=" << attributeId;


                        } else {
                            BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointId << ", cluster="
                                                     << clusterId << ", attribute=" << attributeId << ", cause: data length differs from attribute effective length";
                            attribute->setStatus(StatusEnum::FAILURE);
                        }
                        singletons->getZigbeeDevice()->setAttribute(key, attribute);
                    } else {
                        BOOST_LOG_TRIVIAL(error) << "Invalid attribute "<< key;
                    }
                } else {
                    BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointId << ", cluster=" << clusterId
                                             << ", attribute=" << attributeId << ", cause: " << status;
                }
            } catch (boost::bad_lexical_cast &e) {
                BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
            }
        }

    private:
        SingletonObjects * singletons;
    };
}

#endif //DOMUS_ENGINE_READATTRIBUTERESPONSESERIAL_H
