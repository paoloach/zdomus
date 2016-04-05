//
// Created by paolo on 03/04/16.
//
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>


#include "ExecuteBind.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../ZigbeeData/Exceptions/InvalidOutCluster.h"
#include "../../ZigbeeData/Exceptions/InvalidInCluster.h"


void zigbee::http::ExecuteBind::operator()(const zigbee::http::PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    auto srcDevice(placeHolder.get<NwkAddr>("srcDevice"));
    auto srcEndpoint(placeHolder.get<EndpointID>("srcEndpoint"));
    auto clusterId(placeHolder.get<ClusterID>("cluster"));
    auto dstDevice(placeHolder.get<NwkAddr>("dstDevice"));
    auto dstEndpoint(placeHolder.get<EndpointID>("dstEndpoint"));

    auto srcZDevice = singletons.getZDevices()->getDevice(srcDevice);
    auto srcZEndpoint = srcZDevice.getEndpoint(srcEndpoint);
    if (!srcZEndpoint.isOutCluster(clusterId)){
        throw InvalidOutCluster(srcDevice, srcEndpoint, clusterId);
    }

    auto dstZDevice = singletons.getZDevices()->getDevice(dstDevice);
    auto dstZEndpoint = dstZDevice.getEndpoint(dstEndpoint);
    if (!dstZEndpoint.isInCluster(clusterId)){
        throw InvalidInCluster(srcDevice, srcEndpoint, clusterId);
    }

    NwkAddr coordinator;
    if (bind) {
        singletons.getZigbeeDevice()->sendReqBind(coordinator, srcZDevice.getExtAddr().asArray(), srcEndpoint, clusterId, dstZDevice.getExtAddr().asArray(), dstEndpoint);
    } else {
        singletons.getZigbeeDevice()->sendReqUnbind(coordinator, srcZDevice.getExtAddr().asArray(), srcEndpoint, clusterId, dstZDevice.getExtAddr().asArray(), dstEndpoint);
    }
}

