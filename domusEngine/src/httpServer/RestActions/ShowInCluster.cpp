/*
 * ShowInCluster.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */


#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include "pistache/http_header.h"

#include "ShowInCluster.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ClusterPT.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowInCluster::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            auto contentType = request.headers().get<ContentType>();
            const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);

            auto device = request.param(":device").as<NwkAddr>();
            auto endpoint = request.param(":endpoint").as<EndpointID>();
            auto clusterId = request.param(":cluster").as<ClusterID>();
            auto zDevice = singletons.getZDevices()->getDevice(device);
            auto zEndpoint = zDevice->getEndpoint(boost::lexical_cast<EndpointID>(endpoint));

            std::stringstream output;

            if (zEndpoint.isInCluster(clusterId)) {
                auto cluster = singletons.getClusters()->getCluster(device, endpoint, clusterId);
                producer.produce(output, ClusterPT(cluster));
                response.send(Code::Ok, output.str());
            } else {
                output << "ERROR: " << "cluster " << clusterId << " is not a cluster of endpoint " << zEndpoint.getEndpoint() << " in the device with address "
                       << zEndpoint.getNwkAddr();
                BOOST_LOG_TRIVIAL(error) << output.str();
                response.send(Code::Bad_Request, output.str());
            }
            return Net::Rest::Route::Result::Ok;
        }

    } /* namespace http */
} /* namespace zigbee */

