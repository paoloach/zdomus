/*
 * ShowDevice.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>

#include "ShowDevice.h"

#include "../RestParser/PlaceHolders.h"
#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicePT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
namespace http {

void ShowDevice::operator ()(const PlaceHolders&& placeHolder, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	const auto & producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
	auto device(placeHolder.get<NwkAddr>("device"));
	producer.produce(response.send(), ZDevicePT(singletons.getZDevices()->getDevice(device)));
}

} /* namespace http */
} /* namespace zigbee */


