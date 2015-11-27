/*
 * ShowOutCluster.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <boost/lexical_cast.hpp>

#include "ShowOutCluster.h"

#include "../RestParser/PlaceHolders.h"
#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ClusterPT.h"
#include "../../ZigbeeData/ZDevices.h"
namespace zigbee {
namespace http {

void ShowOutCluster::operator ()(const PlaceHolders&& placeHolder, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	const auto & producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
	auto nwkAddr(placeHolder.get<NwkAddr>("device"));
	auto endpoint(placeHolder.get<EndpointID>("endpoint"));
	auto clusterId(placeHolder.get<ClusterID>("cluster"));
	auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(nwkAddr));
	auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
	if (zEndpoint.isOutCluster(clusterId)) {
		auto zigbeeDevice = singletons.getZigbeeDevice();
		auto cluster = singletons.getClusterTypeFactory()->getCluster(clusterId, zigbeeDevice, endpoint, nwkAddr);
		producer.produce(response.send(), ClusterPT(cluster));
	} else {
		std::stringstream message;

		message << "ERROR: " << "cluster " << clusterId << " is not an OUT cluster of endpoint " << zEndpoint.getEndpoint() << " in the device with address " << zEndpoint.getNwkAddr();
		std::cerr << message.str() << std::endl;
		response.send() << message.str();
		response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
	}
}

} /* namespace http */
} /* namespace zigbee */

