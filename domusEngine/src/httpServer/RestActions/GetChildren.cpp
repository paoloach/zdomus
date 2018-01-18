//
// Created by paolo on 16/01/18.
//
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>

#include "../../Utils/SingletonObjects.h"

#include "GetChildren.h"
#include "../../json/json/json.h"

namespace zigbee {
    using namespace Json;
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Route::Result GetChildren::operator()(const Pistache::Rest::Request &request, ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto device = request.param(":device").as<NwkAddr>();
        BOOST_LOG_TRIVIAL(trace) << "getChildren " << device;
        auto zigbeeDevice = singletons->getZigbeeDevice();
        zigbeeDevice->registerForIEEEAddress(device, std::make_unique<GetChildrenCallback>(std::move(response)));
        zigbeeDevice->getIEEEAddress(device, ZDPRequestType::Extended, 0);
        return Route::Result::Ok;
    }

    void GetChildrenCallback::response(std::shared_ptr<IEEEAddressResponse> response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "arrived IEEE address for " << response->nwkAddr;
        Value root(objectValue);
        root["nwkId"] = boost::lexical_cast<std::string>(response->nwkAddr);
        root["extendAddr"] = boost::lexical_cast<std::string>(response->ieeeAddr);
        root["startIndex"] = std::to_string(response->startIndex);
        root["totalDevice"] = std::to_string(response->totalDevice);
        Value children(arrayValue);
        for(auto child: response->children){
            Value jsonChild(boost::lexical_cast<std::string>(child));
            children.append(jsonChild);
        }
        root["children"] = children;
        std::stringstream stream;

        stream << root << "\n\r";
        BOOST_LOG_TRIVIAL(info) << "response: " << stream.str();

        responseWriter.send(Code::Ok, stream.str());
    }

    void GetChildrenCallback::timeout() {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "IEEE children timeout";
        responseWriter.send(Code::Internal_Server_Error);
    }
}


