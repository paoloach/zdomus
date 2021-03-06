//
// Created by paolo on 12/05/17.
//


#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <functional>
#include <boost/log/attributes/named_scope.hpp>

#include "ShowPowerNode.h"
#include "../../json/json/json.h"

namespace zigbee::http {
    using namespace Json;
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;


    Pistache::Rest::Route::Result ShowPowerNode::operator()(const Pistache::Rest::Request &request, ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto device = request.param(":device").as<NwkAddr>();
        BOOST_LOG_TRIVIAL(trace) << "ShowPower " << device;
        auto zigbeeDevice = singletons->getZigbeeDevice();
        zigbeeDevice->registerForPowerNode(device, std::make_unique<ShowPowerNodeCallback>(std::move(response)));
        zigbeeDevice->requestNodePower(device);

        return Pistache::Rest::Route::Result::Ok;
    }

    void ShowPowerNodeCallback::response(std::shared_ptr<PowerNodeData> powerNodeData) {
        BOOST_LOG_TRIVIAL(info) << "arrived power node for address " << powerNodeData->nwkAddr;
        Value root(objectValue);
        root["error"] = powerNodeData->error;
        root["nwkId"] = boost::lexical_cast<std::string>(powerNodeData->nwkAddr);
        root["powerLevel"] = toString(powerNodeData->currentPowerSourceLevel);
        root["powerMode"] = toString(powerNodeData->powerMode);
        root["availablePowerSource"] = powerNodeData->availablePowerSource.getValue();
        root["currentPowerSource"] = powerNodeData->currentPowerSource.getValue();
        std::stringstream stream;

        stream << root << "\n\r";

        responseWriter.send(Code::Ok, stream.str());
    }

    void ShowPowerNodeCallback::timeout() {
        BOOST_LOG_TRIVIAL(info) << "Power node timeout";
        responseWriter.send(Code::Internal_Server_Error);
    }
} /* namespace zigbee */