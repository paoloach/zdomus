/*
 * ShowInCluster.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <boost/log/attributes/named_scope.hpp>
#include "pistache/http_header.h"

#include "ShowInCluster.h"

#include "../MediaTypeProducerFactory.h"
#include "../../ZigbeeData/PropertyTree/ClusterPT.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../Utils/Clusters.h"

namespace zigbee::http {
    using namespace Pistache::Rest;
    using namespace Pistache::Http;
    using namespace Pistache::Http::Header;

    Pistache::Rest::Route::Result ShowInCluster::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) {
        BOOST_LOG_NAMED_SCOPE("HTTP");
        auto contentType = request.headers().get<ContentType>();
        const auto &producer = MediaTypeProducerFactory::getMediaType(contentType);

        auto device = request.param(":device").as<NwkAddr>();
        auto endpoint = request.param(":endpoint").as<EndpointID>();
        auto clusterId = request.param(":cluster").as<ClusterID>();
        auto zDevice = singletons->getZDevices()->getDevice(device);
        auto zEndpoint = zDevice->getEndpoint(boost::lexical_cast<EndpointID>(endpoint));

        std::stringstream output;

        if (zEndpoint.isInCluster(clusterId)) {
            auto cluster = singletons->getClusters()->getCluster(device, endpoint, clusterId);
            producer.produce(output, ClusterPT(cluster));
            response.send(Code::Ok, output.str());
        } else {
            output << "ERROR: " << "cluster " << clusterId << " is not a cluster of endpoint " << zEndpoint.getEndpoint() << " in the device with address "
                   << zEndpoint.getNwkAddr();
            BOOST_LOG_TRIVIAL(error) << output.str();
            response.send(Code::Bad_Request, output.str());
        }
        return Pistache::Rest::Route::Result::Ok;
    }

} /* namespace zigbee */

