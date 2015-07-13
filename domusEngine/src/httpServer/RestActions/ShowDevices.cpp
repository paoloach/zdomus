/*
 * ShowDevices.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>

#include "ShowDevices.h"

#include "../RestParser/PlaceHolders.h"
#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
namespace http {

void ShowDevices::operator ()(const PlaceHolders&& placeHolder, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	const auto & producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
	std::ostream& stream = response.send();
	producer.produce(stream, ZDevicesPT(singletons.getZDevices()));
}

} /* namespace http */
} /* namespace zigbee */

