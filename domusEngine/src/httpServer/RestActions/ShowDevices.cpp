/*
 * ShowDevices.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <sstream>

#include "ShowDevices.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowDevices::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter  && response) {
            auto contentType = request.headers().get<ContentType>();
            const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);
            std::stringstream output;
            producer.produce(output, ZDevicesPT(singletons.getZDevices()));
            response.send(Code::Ok, output.str());
            return Net::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

