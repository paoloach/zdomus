/*
 * ShowAttribute.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <chrono>
#include <thread>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <zigbee/AttributesKey.h>
#include "ShowAttribute.h"

#include "../MediaTypeProducerFactory.h"
#include "../../ZigbeeData/PropertyTree/AttributePT.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../json/json/json.h"
#include "../../Utils/Clusters.h"

using namespace Json;
using namespace std::chrono;
using std::string;
using std::vector;

namespace zigbee {
    namespace http {
        using namespace Pistache::Rest;
        using namespace Pistache::Http;
        using namespace Pistache::Http::Header;
        using namespace std::literals::chrono_literals;

        ShowAttribute::ShowAttribute(SingletonObjects * singletons, const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) :
                singletons(singletons), responseWriter(std::move(response)) {
            BOOST_LOG_NAMED_SCOPE("HTTP");

            key.networkAddress = request.param(":device").as<NwkAddr>();
            key.endpoint = request.param(":endpoint").as<EndpointID>();
            key.clusterId = request.param(":cluster").as<ClusterID>();

            auto zDevice = singletons->getZDevices()->getDevice(key.networkAddress);
            auto zEndpoint = zDevice->getEndpoint(key.endpoint);
            if (zEndpoint.isInCluster(key.clusterId)) {
                auto zigbeeDevice = singletons->getZigbeeDevice();
                auto cluster(singletons->getClusters()->getCluster(key.networkAddress, key.endpoint, key.clusterId));
                auto idAttribute = request.query().get("id");
                if (!idAttribute.isEmpty()) {
                    std::stringstream stream(idAttribute.get());
                    ZigbeeAttributeIds attributesId;
                    stream >> attributesId;
                    key.attributesId = attributesId;

                    if (zigbeeDevice != nullptr) {
                        zigbeeDevice->requestAttributes(key);
                    }
                } else {
                    BOOST_LOG_TRIVIAL(error) << "Available in clusters are";
                    for (auto &inCluster: zEndpoint.getInCluster()) {
                        BOOST_LOG_TRIVIAL(error) << inCluster.getId();
                    }
                    throwWrongCluster(std::move(responseWriter), key.clusterId, key.endpoint, key.networkAddress);
                }
            } else {
                responseWriter.send(Code::Bad_Request);
            }
        }


        void ShowAttribute::response(std::vector<ZCLAttribute *> && attributes ){
            if (allTimeout(attributes)){
                responseWriter.send(Code::Bad_Request, "data error\n\r");
            } else {
                Value root(arrayValue);

                for (auto &&attribute : attributes) {
                    if (attribute != nullptr) {
                        Value jsonAttribute(objectValue);

                        jsonAttribute["id"] = Value(attribute->getIdentifier());
                        jsonAttribute["name"] = Value(std::string(attribute->getName()));
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
                }
                std::stringstream stream;
                stream << root << "\r\n";
                responseWriter.send(Code::Ok, stream.str(), MIME(Application, Json));
            }
        }

    } /* namespace http */
} /* namespace zigbee */

