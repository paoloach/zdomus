/*
 * ShowDevices.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>

#include "ShowDevices.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

namespace zigbee {
  namespace http {

    void ShowDevices::operator()(const PlaceHolders &&, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        BOOST_LOG_TRIVIAL(info) << "ShowDevices";
        const auto &producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
        producer.produce(response.send(), ZDevicesPT(singletons.getZDevices()));
    }

  } /* namespace http */
} /* namespace zigbee */

