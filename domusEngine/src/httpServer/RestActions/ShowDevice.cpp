/*
 * ShowDevice.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>

#include "ShowDevice.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicePT.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../ZigbeeData/Exceptions/InvalidZDevice.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowDevice::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            auto contentType = request.headers().get<ContentType>();
            const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);
            try {
                auto device = request.param(":device").as<NwkAddr>();
                BOOST_LOG_TRIVIAL(info) << "Request device configuration " << device;
                auto zDevice = singletons.getZDevices()->getDevice(device);
                std::stringstream output;
                producer.produce(output, ZDevicePT(zDevice));
                response.send(Code::Ok, output.str());
                return Net::Rest::Route::Result::Ok;
            } catch (InvalidZDevice e){
                response.send(Code::Not_Found, e.getMessage());
                return Net::Rest::Route::Result::Ok;
            }
        }

    } /* namespace http */
} /* namespace zigbee */


