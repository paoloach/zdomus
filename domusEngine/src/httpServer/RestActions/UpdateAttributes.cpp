//
// Created by paolo on 23/06/16.
//

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "UpdateAttributes.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../ServerRequest.h"

using  Json::operator>>;


namespace zigbee {
    namespace http {

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
        void UpdateAttributes::operator()(const PlaceHolders &&placeHolder,ServerRequest & request, Poco::Net::HTTPServerResponse &response) {
            auto nwkAddr(placeHolder.get<NwkAddr>("device"));
            auto endpoint(placeHolder.get<EndpointID>("endpoint"));
            auto clusterId(placeHolder.get<ClusterID>("cluster"));
            auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(nwkAddr));
            auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
            if (zEndpoint.isInCluster(clusterId)) {
                auto cluster(singletons.getClusters()->getCluster(nwkAddr,endpoint, clusterId));

                if (!request.isApplicationJSon()){
                    BOOST_LOG_TRIVIAL(error) << "requested content type " << request.getContentType();
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                    response.send() <<"Accepted only application/json type\r\n";
                    return ;
                }

                Json::Value root;
                request.stream() >> root;

                auto results = singletons.getAttributeWriter().write(nwkAddr, endpoint, cluster, root);
                Poco::Net::MediaType mediaType("application", "json");
                response.setContentType(mediaType);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                response.send() << results.toJSon() << "\r\n";
            } else {
                throwWrongCluster(response, clusterId, endpoint, nwkAddr);
            }
        }

    } /* namespace http */
} /* namespace zigbee */
