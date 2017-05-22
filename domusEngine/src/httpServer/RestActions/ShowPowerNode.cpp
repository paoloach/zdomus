//
// Created by paolo on 12/05/17.
//


#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include <functional>

#include "../../Utils/SingletonObjects.h"
#include "ShowPowerNode.h"
#include "../../json/json/json.h"

namespace zigbee {
    namespace http {
        using namespace Json;
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;


        Net::Rest::Route::Result ShowPowerNode::operator()(const Net::Rest::Request &request, ResponseWriter &&response) {
            auto device = request.param(":device").as<NwkAddr>();
            BOOST_LOG_TRIVIAL(trace) << "ShowPower " << device;
            auto showPowerNodeCallback = std::make_unique<ShowPowerNodeCallback>(std::move(response));
            singletons.getZigbeeDevice()->registerForPowerNode(device, std::move(showPowerNodeCallback));
            singletons.getZigbeeDevice()->requestNodePower(device);

            return Net::Rest::Route::Result::Ok;
        }

        void ShowPowerNodeCallback::response(std::shared_ptr<PowerNodeData> powerNodeData) {
            BOOST_LOG_TRIVIAL(info) << "arrived power node for address " << powerNodeData->nwkAddr;
            Value root(objectValue);
            root["nwkId"] = powerNodeData->nwkAddr.getId();
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
    } /* namespace http */
} /* namespace zigbee */