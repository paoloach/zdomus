/*
 * ShowEndpoint.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */


#include <zigbee/NwkAddr.h>
#include <boost/log/trivial.hpp>

#include "ShowEndpoint.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZEndpointPT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowEndpoint::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            auto contentType = request.headers().get<ContentType>();
            const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);

            auto device = request.param(":device").as<NwkAddr>();
            auto endpoint = request.param(":endpoint").as<EndpointID>();
            BOOST_LOG_TRIVIAL(trace) << "ShowEndpoint " << device << ":" << endpoint;
            auto zDevice = singletons.getZDevices()->getDevice(device);
            std::stringstream output;
            producer.produce(output, ZEndpointPT(zDevice->getEndpoint(endpoint)));
            response.send(Code::Ok, output.str());
            return Net::Rest::Route::Result::Ok;
        }

    } /* namespace http */
} /* namespace zigbee */

