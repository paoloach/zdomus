//
// Created by paolo on 04/10/16.
//
#include <zigbee/NwkAddr.h>
#include "../../json/json/json.h"
#include "../../ZigbeeData/ZDevices.h"
#include <zcl/ClusterTypeFactory.h>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/lexical_cast.hpp>

#include "ShowTopology.h"

using namespace Json;

namespace zigbee::http {
    using std::string;
    using boost::lexical_cast;
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Pistache::Rest::Route::Result ShowTopology::operator()(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");

        BOOST_LOG_TRIVIAL(info) << "ShowTopology";
        auto zDevices = singletons->getZDevices();
        auto rootDevice = zDevices->getDeviceNoExcept(NwkAddr{0});
        Value root(objectValue);

        root["nwkId"] = Value(0);
        root["ieeeAddress"] = Value(rootDevice->getExtAddr().asString());
        root["capability"] = Value(rootDevice->getCapabilities());
        auto children = rootDevice->getChildren();
        root["children"] = createChildren(children);
        std::stringstream stream;

        stream << root << "\n\r";


        response.send(Code::Ok, stream.str());

        return Pistache::Rest::Route::Result::Ok;
    }

    Json::Value ShowTopology::createChildren(std::set<NwkAddr> &children) {
        Value jSonChildren(arrayValue);

        for (NwkAddr child: children) {
            jSonChildren.append(createNode(child));
        }

        return jSonChildren;
    }

    Json::Value ShowTopology::createNode(NwkAddr &nwkAddr) {
        Value child(objectValue);

        auto zDevices = singletons->getZDevices();
        auto node = zDevices->getDeviceNoExcept(nwkAddr);
        child["nwkId"] = Value(lexical_cast<string>(nwkAddr));
        if (node != nullptr) {
            child["ieeeAddress"] = Value(node->getExtAddr().asString());
            child["capability"] = Value(node->getCapabilities());
            auto children = node->getChildren();
            child["children"] = createChildren(children);
        }
        return child;
    }
}
