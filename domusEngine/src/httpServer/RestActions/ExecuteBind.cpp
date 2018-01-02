//
// Created by paolo on 03/04/16.
//
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/trivial.hpp>

#include "ExecuteBind.h"

#include "../MediaTypeProducerFactory.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../ZigbeeData/Exceptions/InvalidOutCluster.h"
#include "../../ZigbeeData/Exceptions/InvalidInCluster.h"

Pistache::Rest::Route::Result zigbee::http::ExecuteBind::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter  && response) {
    BOOST_LOG_NAMED_SCOPE("HTTP");
    BOOST_LOG_TRIVIAL(info) << "ExecuteBind";

    auto srcDevice = request.param(":srcDevice").as<NwkAddr>();
    auto srcEndpoint = request.param(":srcEndpoint").as<EndpointID>();
    auto clusterId = request.param(":cluster").as<ClusterID>();
    auto dstDevice = request.param(":dstDevice").as<NwkAddr>();
    auto dstEndpoint = request.param(":dstEndpoint").as<EndpointID>();

    auto srcZDevice = singletons->getZDevices()->getDevice(srcDevice);
    auto srcZEndpoint = srcZDevice->getEndpoint(srcEndpoint);
    if (!srcZEndpoint.isOutCluster(clusterId)) {
        throw InvalidOutCluster(srcDevice, srcEndpoint, clusterId);
    }

    auto dstZDevice = singletons->getZDevices()->getDevice(dstDevice);
    auto dstZEndpoint = dstZDevice->getEndpoint(dstEndpoint);
    if (!dstZEndpoint.isInCluster(clusterId)) {
        throw InvalidInCluster(srcDevice, srcEndpoint, clusterId);
    }

    NwkAddr coordinator(srcDevice);
    if (bind) {
        singletons->getZigbeeDevice()->sendReqBind(coordinator, srcZDevice->getExtAddr().asArray(), srcEndpoint, clusterId, dstZDevice->getExtAddr().asArray(), dstEndpoint);
    } else {
        singletons->getZigbeeDevice()->sendReqUnbind(coordinator, srcZDevice->getExtAddr().asArray(), srcEndpoint, clusterId, dstZDevice->getExtAddr().asArray(), dstEndpoint);
    }
    std::stringstream stream;
    stream << "Cluster " << clusterId << " binded " << srcDevice << ":" << srcEndpoint << " with " << dstDevice << ":" << dstEndpoint << std::endl;

    response.send(Pistache::Http::Code::Ok, stream.str(), MIME(Text, Plain));
    return Pistache::Rest::Route::Result::Ok;
}

