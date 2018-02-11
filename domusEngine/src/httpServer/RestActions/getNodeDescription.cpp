//
// Created by paolo on 31/01/18.
//

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <pistache/http.h>

#include "../../Utils/SingletonObjects.h"

#include "getNodeDescription.h"
#include "../../json/json/json.h"

namespace zigbee {
    using namespace Json;
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Route::Result GetNodeDescription::operator()(const Pistache::Rest::Request &request, ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto device = request.param(":device").as<NwkAddr>();
        BOOST_LOG_TRIVIAL(trace) << " getNodeDescriptor " << device;
        auto zigbeeDevice = singletons->getZigbeeDevice();
        zigbeeDevice->registerForNodeDescriptor(device, std::make_unique<GetNodeDescriptionCallback>(std::move(response)));
        zigbeeDevice->getNodeDescriptor(device);
        return Route::Result::Ok;
    }

    void GetNodeDescriptionCallback::response(std::shared_ptr<NodeDescriptorResponse> response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "arrived NodeDescriptor for " << response->nwkAddr;
        Value root(objectValue);
        root["nwkId"] = boost::lexical_cast<std::string>(response->nwkAddr);
        root["logicalType"] = toString(response->logicalType);
        root["bandFrequency"] = std::to_string(response->bandFrequency);
        root["macCapability"] = std::to_string(response->macCapability);

        root["manufactorerCode"] = std::to_string(response->manufactorerCode);
        root["maximumBufferSize"] = std::to_string(response->maximumBufferSize);
        root["maximumIncomingTransferSize"] = std::to_string(response->maximumIncomingTransferSize);
        root["serverMask"] = std::to_string(response->serverMask);
        root["maximumOutcomingTransferSize"] = std::to_string(response->maximumOutcomingTransferSize);
        root["descriptorCapability"] = std::to_string(response->descriptorCapability);

        std::stringstream stream;

        stream << root << "\n\r";
        BOOST_LOG_TRIVIAL(info) << "response: " << stream.str();

        responseWriter.send(Code::Ok, stream.str());
    }

    void GetNodeDescriptionCallback::timeout() {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "NodeDescriptor timeout";
        responseWriter.send(Code::Internal_Server_Error);
    }


    std::string GetNodeDescriptionCallback::toString(LogicalType logicalType) {
        switch (logicalType){
            case LogicalType::ZigbeeCordinator:
                return "coordinator";
            case LogicalType::ZigbeeRouter:
                return "router";
            case LogicalType::ZigbeeEnddevice:
                return "end device";
        }
        return std::string();
    }

}


