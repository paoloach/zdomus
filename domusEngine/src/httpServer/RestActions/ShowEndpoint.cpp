/*
 * ShowEndpoint.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */


#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <boost/lexical_cast.hpp>

#include "ShowEndpoint.h"

#include "../RestParser/PlaceHolders.h"
#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZEndpointPT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
    namespace http {

        void ShowEndpoint::operator()(const PlaceHolders &&placeHolder, ServerRequest &request,
                                      Poco::Net::HTTPServerResponse &response) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            const auto &producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
            auto device(placeHolder.get<NwkAddr>("device"));
            auto endpoint(placeHolder.get<EndpointID>("endpoint"));
            auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(device));
            producer.produce(response.send(), ZEndpointPT(zDevice.getEndpoint(endpoint)));
        }

    } /* namespace http */
} /* namespace zigbee */

