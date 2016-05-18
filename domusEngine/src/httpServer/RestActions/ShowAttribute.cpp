/*
 * ShowAttribute.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <chrono>
#include <thread>

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "ShowAttribute.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/AttributePT.h"
#include "../../ZigbeeData/ZDevices.h"

#include "../../json/json/json.h"

using namespace Json;
using std::string;
using boost::tokenizer;
using std::vector;

namespace zigbee {
    namespace http {

        void ShowAttribute::operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &,
                                       Poco::Net::HTTPServerResponse &response) {
            auto nwkAddr(placeHolder.get<NwkAddr>("device"));
            auto endpoint(placeHolder.get<EndpointID>("endpoint"));
            auto clusterId(placeHolder.get<ClusterID>("cluster"));
            auto zDevice = singletons.getZDevices()->getDevice(nwkAddr);
            auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
            if (zEndpoint.isInCluster(clusterId)) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                auto zigbeeDevice = singletons.getZigbeeDevice();
                auto cluster(singletons.getClusterTypeFactory()->getCluster(clusterId, zigbeeDevice, endpoint, nwkAddr));
                ZigbeeAttributeIds attributesId (placeHolder.getQueryParams<ZigbeeAttributeId>("id"));
                vector<std::shared_ptr<ZCLAttribute>> attributes;
                attributesArrived = std::vector<std::atomic<bool >>(attributesId.size());

                int index = 0;
                for (int attributeId: attributesId) {
                    auto attribute = cluster->getAttribute(attributeId);
                    attributes.push_back(attribute);
                    std::atomic_init(&attributesArrived[index], false);
                    mapAttributes[attributeId] = index;
                    index++;
                    NewAttributeValueCallback fn = [this, attributeId](int status) { this->attributeReceived(attributeId, status); };
                    if (attribute) {
                        singletons.getAttributeValueSignalMap().insert(AttributeKey{nwkAddr, endpoint.getId(), clusterId.getId(),
                                                                                    static_cast<ZigbeeAttributeId>(attribute->getIdentifier())}, fn);
                    }
                }
                if (zigbeeDevice != nullptr) {
                    zigbeeDevice->requestAttributes(nwkAddr, endpoint, clusterId, attributesId);
                }

                std::chrono::milliseconds duration(100);
                while (!isAllAttributeArrived()) {
                    std::this_thread::sleep_for(duration);
                }
                if (status != 0) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                } else {
                    send(response, std::move(attributes));
                }

            } else {
                throwWrongCluster(response, clusterId, endpoint, nwkAddr);
            }
        }

        void ShowAttribute::send(Poco::Net::HTTPServerResponse &response, std::vector<std::shared_ptr<ZCLAttribute>> &&attributes) {
            response.setContentType(Poco::Net::MediaType("application", "json"));
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
            Value root(arrayValue);

            for (auto &&attribute : attributes) {
                Value jsonAttribute(objectValue);

                jsonAttribute["id"] = Value(attribute->getIdentifier());
                jsonAttribute["name"] = Value(attribute->getName().to_string());
                jsonAttribute["readOnly"] = Value(attribute->isReadOnly());
                jsonAttribute["type"] = Value(static_cast<int>(attribute->getZCLType()));
                jsonAttribute["isAvailable"] = Value(attribute->isAvailable());
                jsonAttribute["isSupported"] = Value(!attribute->isUnsupported());
                jsonAttribute["status"] = Value(attribute->getStatus());
                if (attribute->isAvailable()) {
                    jsonAttribute["value"] = Value(boost::any_cast<std::string>(attribute->getValue()));
                }
                root.append(jsonAttribute);
            }
            response.send() << root << "\n";
        }

        void ShowAttribute::attributeReceived(int id, int status) {
            this->status = status;
            attributesArrived[mapAttributes[id]].store(true);
        }

        bool ShowAttribute::isAllAttributeArrived() const {
            for (auto &arrived: attributesArrived) {
                if (!arrived.load()) {
                    return false;
                }
            }
            return true;
        }


    } /* namespace http */
} /* namespace zigbee */

