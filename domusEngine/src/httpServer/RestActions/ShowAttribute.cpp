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
#include <boost/lexical_cast.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "ShowAttribute.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/AttributePT.h"
#include "../../ZigbeeData/ZDevices.h"

using namespace Json;
using namespace std::chrono;
using std::string;
using std::vector;

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        void ShowAttribute::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response) {
            auto nwkAddr = request.param(":device").as<NwkAddr>();
            auto endpoint = request.param(":endpoint").as<EndpointID>();
            auto clusterId = request.param(":cluster").as<ClusterID>();

            BOOST_LOG_TRIVIAL(trace) << "ShowAttribute (device:" << nwkAddr << ", endpoint:" << endpoint << ", cluster:" << clusterId <<")";
            auto zDevice = singletons.getZDevices()->getDevice(nwkAddr);
            auto zEndpoint = zDevice->getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
            if (zEndpoint.isInCluster(clusterId)) {
                auto zigbeeDevice = singletons.getZigbeeDevice();
                auto cluster(singletons.getClusters()->getCluster(nwkAddr, endpoint, clusterId));
                auto idAttribute = request.query().get("id");
                if (!idAttribute.isEmpty()) {
                    std::stringstream stream(idAttribute.get());
                    ZigbeeAttributeIds attributesId;
                    stream >> attributesId;
                    vector<ZCLAttribute *> attributes;
                    attributesArrived = std::vector<std::atomic<bool >>(attributesId.size());

                    int index = 0;
                    for (int attributeId: attributesId) {
                        auto attribute = cluster->getAttribute(attributeId);
                        attributes.push_back(attribute);
                        std::atomic_init(&attributesArrived[index], false);
                        mapAttributes[attributeId] = index;
                        index++;
                        NewAttributeValueCallback fn = [this, attributeId](int status) {
                            this->attributeReceived(attributeId, status);
                        };
                        if (attribute) {
                            singletons.getAttributeValueSignalMap().insert(
                                    AttributeKey{nwkAddr, endpoint.getId(), clusterId.getId(), static_cast<ZigbeeAttributeId>(attribute->getIdentifier())}, fn);
                        }
                    }
                    if (zigbeeDevice != nullptr) {
                        zigbeeDevice->requestAttributes(nwkAddr, endpoint, clusterId, attributesId);
                    }

                    std::chrono::milliseconds duration(100);
                    auto start = system_clock::now();
                    while (!isAllAttributeArrived()) {
                        std::this_thread::sleep_for(duration);
                        milliseconds elapsed = duration_cast<std::chrono::milliseconds>(system_clock::now() - start);
                        if (elapsed > minutes(10)) {
                            response.send(Code::Bad_Request, "data timeout\n\r");
                            return;
                        }
                    }
                    BOOST_LOG_TRIVIAL(trace) << "all the attribute received";
                    if (status != 0) {
                        response.send(Code::Bad_Request, "data error\n\r");
                    } else {
                        BOOST_LOG_TRIVIAL(debug) << "All the " << attributes.size() << " arrived";
                        send(std::move(response), std::move(attributes));
                    }
                } else {
                    BOOST_LOG_TRIVIAL(error) << "Available in clusters are";
                    for (auto &inCluster: zEndpoint.getInCluster()) {
                        BOOST_LOG_TRIVIAL(error) << inCluster.getId();
                    }
                    throwWrongCluster(response, clusterId, endpoint, nwkAddr);
                }
            } else {
                response.send(Code::Bad_Request);
            }
        }

        void ShowAttribute::send(Net::Http::ResponseWriter && response,
                                 std::vector<ZCLAttribute * > &&attributes) {
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
                    jsonAttribute["value"] = attribute->getStrValue();
                }
                root.append(jsonAttribute);
            }
            std::stringstream stream;
            stream << root << "\r\n";
            response.send(Code::Ok, stream.str(), MIME(Application, Json));
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

