/*
 * ShowDevices.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <sstream>
#include <boost/log/attributes/named_scope.hpp>

#include "ShowDevices.h"

#include "../MediaTypeProducerFactory.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

namespace zigbee::http {
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Pistache::Rest::Route::Result ShowDevices::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        if (request.headers().has(ContentType::Name)) {
            auto contentType = request.headers().get<ContentType>();
            const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);
            std::stringstream output;
            producer.produce(output, ZDevicesPT(singletons->getZDevices()));
            response.send(Code::Ok, output.str());
            return Pistache::Rest::Route::Result::Ok;
        } else {
            response.send(Code::Bad_Request, "Invalid content type\n\r");
            return Pistache::Rest::Route::Result::Ok;
        }
    }
} /* namespace zigbee */

