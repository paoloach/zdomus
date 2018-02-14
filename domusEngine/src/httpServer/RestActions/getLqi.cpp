//
// Created by paolo on 13/02/18.
//

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <pistache/http.h>

#include "../../Utils/SingletonObjects.h"

#include "getLqi.h"
#include "../../json/json/json.h"

namespace zigbee {
    using namespace Json;
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Pistache::Rest::Route::Result GetLqi::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto device = request.param(":device").as<NwkAddr>();
        uint index=0;
        auto queryIndex = request.query().get("index");
        if (!queryIndex.isEmpty()){
            index =  boost::lexical_cast<uint>(queryIndex.get());
        }

        BOOST_LOG_TRIVIAL(trace) << " getLqi " << device;
        auto zigbeeDevice = singletons->getZigbeeDevice();
        zigbeeDevice->registerForLQIResponse(device, std::make_unique<GetLqiCallback>(std::move(response)));
        zigbeeDevice->getLqiResponse(device,index);
        return Route::Result::Ok;
    }

    void GetLqiCallback::response(std::shared_ptr<LqiResponse> response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "arrived NodeDescriptor for " << response->nwkAddr;
        Value root(objectValue);
        root["index"] = response->index;
        root["totalTables"] = response->totalTables;
        root["panAddr"] = boost::lexical_cast<std::string>(response->panAddr);
        root["ieeeAddr"] = boost::lexical_cast<std::string>(response->ieeeAddr);
        root["nwkId"] = boost::lexical_cast<std::string>(response->nwkAddr);
        root["logicalType"] = toString(response->logicalType);
        root["onWhenIdle"] = response->onWhenIdle;
        root["relationship"] = toString(response->relationship);
        root["neighborAcceptJoin"] = response->neighborAcceptJoin;
        root["depth"] = response->depth;
        root["lqi"] = response->lqi;

        std::stringstream stream;

        stream << root << "\n\r";
        BOOST_LOG_TRIVIAL(info) << "response: " << stream.str();

        responseWriter.send(Code::Ok, stream.str());
    }

    void GetLqiCallback::timeout() {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        BOOST_LOG_TRIVIAL(info) << "NodeDescriptor timeout";
        responseWriter.send(Code::Internal_Server_Error);
    }

    std::string GetLqiCallback::toString(LogicalType logicalType) {
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

    std::string GetLqiCallback::toString(Relationship relationship) {
        switch (relationship){
            case Relationship::NeighborIsParent:
                return "NeighborIsParent";
            case Relationship::NeighborIsChild:
                return "NeighborIsChild";
            case Relationship::NeighborIsSibling:
                return "NeighborIsSibling";
            case Relationship::NoRelation:
                return "NoRelation";
            case Relationship::PreviousChild:
                return "PreviousChild";
        }
        return std::string();
    }
}