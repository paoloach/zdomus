//
// Created by paolo on 23/06/16.
//

#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "UpdateAttributes.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"

using Json::operator>>;


namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        /**
         * {
         * "attributes":
         *       [
         *         {
         *          "id":"value",
         *          "type":"raw",
         *         "data":[12,43,34,3]
         *         },
         *         {
         *          "id":"value",
         *          "type":"int",
         *         "data":"12345"
         *         },
         *         {
         *         "id":"atributeId",
         *         "type":"string",
         *         "data":"string"
         *       ]
         *
         * }
         *
         */
        Net::Rest::Route::Result UpdateAttributes::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            BOOST_LOG_TRIVIAL(info) << "UpdateAttributes";
            auto nwkAddr = request.param(":device").as<NwkAddr>();
            auto endpoint = request.param(":endpoint").as<EndpointID>();
            auto clusterId = request.param(":cluster").as<ClusterID>();

            auto zDevice = singletons.getZDevices()->getDevice(nwkAddr);
            auto zEndpoint = zDevice->getEndpoint(endpoint);
            if (zEndpoint.isInCluster(clusterId)) {
                auto contentType = request.headers().get<ContentType>();
                auto cluster(singletons.getClusters()->getCluster(nwkAddr, endpoint, clusterId));

                if (!(contentType->mime() == MIME(Application, Json)) ) {
                    BOOST_LOG_TRIVIAL(error) << "requested content type " << contentType->mime().toString();
                    response.send(Code::Not_Acceptable, "Accepted only application/json type\r\n");

                } else {

                    Json::Value root;
                    std::stringstream stream(request.body());
                    stream >> root;

                    auto results = singletons.getAttributeWriter().write(nwkAddr, endpoint, cluster, root);
                    response.send(Code::Ok, results.toJSon(), MIME(Application, Json));
                }
            } else {
                throwWrongCluster(response, clusterId, endpoint, nwkAddr);
            }
            return Net::Rest::Route::Result::Ok;
        }

    } /* namespace http */
} /* namespace zigbee */
