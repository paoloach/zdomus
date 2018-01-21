//
// Created by paolo on 20/01/18.
//
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>

#include <pistache/router.h>
#include <pistache/http_defs.h>
#include "DeleteDevice.h"
#include "../../Utils/SingletonObjects.h"
namespace zigbee::http {
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Pistache::Rest::Route::Result DeleteDevice::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto device = request.param(":device").as<NwkAddr>();
        BOOST_LOG_TRIVIAL(trace) << "remove device " << device;
        singletons->getZigbeeDevice()->removeDevice(device);
        response.send(Code::No_Content);
        return Route::Result::Ok;
    }
}