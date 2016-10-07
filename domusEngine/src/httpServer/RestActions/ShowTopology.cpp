//
// Created by paolo on 04/10/16.
//
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include "../../json/json/json.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <boost/log/trivial.hpp>

#include "ShowTopology.h"

using namespace Json;

namespace zigbee {
    namespace http {

        void ShowTopology::operator()(const PlaceHolders &&,
                                      ServerRequest &,
                                      Poco::Net::HTTPServerResponse &response) {

            BOOST_LOG_TRIVIAL(info) << "ShowTopology";
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

            auto zDevices = singletons.getZDevices();
            auto rootDevice = zDevices->getDeviceNoExcept(NwkAddr{0});
            Value root(objectValue);

            root["nwkId"] = Value(0);
            root["ieeeAddress"] = Value(rootDevice->getExtAddr().asString());
            root["capability"] = Value(rootDevice->getCapabilities());
            auto children = rootDevice->getChildren();
            root["children"] = createChildren(children);

            response.send() << root << "\n";

        }

        Json::Value ShowTopology::createChildren(std::set<NwkAddr> &children) {
            Value jSonChildren(arrayValue);

            for (NwkAddr child: children) {
                jSonChildren.append( createNode(child));
            }

            return jSonChildren;
        }

        Json::Value ShowTopology::createNode(NwkAddr &nwkAddr) {
            Value child(objectValue);

            auto zDevices = singletons.getZDevices();
            auto node = zDevices->getDeviceNoExcept(nwkAddr);
            child["nwkId"] = Value(nwkAddr.getId());
            if (node != nullptr) {
                child["ieeeAddress"] = Value(node->getExtAddr().asString());
                child["capability"] = Value(node->getCapabilities());
                auto children = node->getChildren();
                child["children"] = createChildren(children);
            }
            return child;
        }
    }
}
