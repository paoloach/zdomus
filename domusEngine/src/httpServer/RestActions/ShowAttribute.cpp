/*
 * ShowAttribute.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <chrono>
#include <thread>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "ShowAttribute.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/AttributePT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
  namespace http {

    void ShowAttribute::operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
        const auto &producer = MediaTypeProducerFactory::getMediaType(request.getContentType());
        auto nwkAddr(placeHolder.get<NwkAddr>("device"));
        auto endpoint(placeHolder.get<EndpointID>("endpoint"));
        auto clusterId(placeHolder.get<ClusterID>("cluster"));
        auto attributeParam(placeHolder.get<std::string>("attribute"));
        auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(nwkAddr));
        auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
        if (zEndpoint.isInCluster(clusterId)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            auto zDevice = singletons.getZigbeeDevice();
            auto cluster(singletons.getClusterTypeFactory()->getCluster(clusterId, zDevice, endpoint, nwkAddr));
            std::shared_ptr<ZCLAttribute> attribute;
            try {
                auto attributeId = boost::lexical_cast<int>(attributeParam);
                attribute = cluster->getAttribute(attributeId);
            } catch (boost::bad_lexical_cast &badCast) {
                attribute = cluster->getAttribute(attributeParam);
            }
            attribute->requestValue();
            std::chrono::milliseconds duration(5);
            while (!attribute->isAvailable()) {
                std::this_thread::sleep_for(duration);
            }
            producer.produce(response.send(), AttributePT(attribute));

        } else {
            throwWrongCluster(response, clusterId, endpoint, nwkAddr);
        }
    }

  } /* namespace http */
} /* namespace zigbee */

