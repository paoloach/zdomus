//
// Created by paolo on 23/06/16.
//

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "UpdateAttributes.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../json/json/json.h"

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
        void UpdateAttributes::operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse &response) {
            auto nwkAddr(placeHolder.get<NwkAddr>("device"));
            auto endpoint(placeHolder.get<EndpointID>("endpoint"));
            auto clusterId(placeHolder.get<ClusterID>("cluster"));
            auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(nwkAddr));
            auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
            if (zEndpoint.isInCluster(clusterId)) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
                response.send() << "comand sent\n";
                auto cluster(singletons.getClusters()->getCluster(nwkAddr,endpoint, clusterId));

                if (request.getContentType() != "application/json"){
                    response.send() <<"\r\n";
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                    return ;
                }

                Json::Value root;
                request.stream() >> root;

                singletons.getAttributeWriter().write(nwkAddr, endpoint, cluster, root);

                auto & attributes = root["attributes"];

            } else {
                throwWrongCluster(response, clusterId, endpoint, nwkAddr);
            }
        }

    } /* namespace http */
} /* namespace zigbee */
