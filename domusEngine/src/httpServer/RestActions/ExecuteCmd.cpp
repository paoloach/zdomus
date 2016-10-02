/*
 * ExecuteCmd.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */


#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>
#include <boost/log/trivial.hpp>

#include "ExecuteCmd.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
  namespace http {

    void ExecuteCmd::operator()(const PlaceHolders &&placeHolder, ServerRequest &, Poco::Net::HTTPServerResponse &response) {
        BOOST_LOG_TRIVIAL(info) << "ExecuteCmd";
        auto nwkAddr(placeHolder.get<NwkAddr>("device"));
        auto endpoint(placeHolder.get<EndpointID>("endpoint"));
        auto clusterId(placeHolder.get<ClusterID>("cluster"));
        auto command(placeHolder.get<int>("command"));
        auto zDevice = singletons.getZDevices()->getDevice(boost::lexical_cast<NwkAddr>(nwkAddr));
        auto zEndpoint = zDevice->getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
        if (zEndpoint.isInCluster(clusterId)) {
            std::vector<uint8_t> cmdParams{};
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
            response.send() << "comand sent\n";
            auto cluster(singletons.getClusters()->getCluster(nwkAddr,endpoint, clusterId));

            auto params = cluster->getCmdParams(command);
            for (const auto &param : params) {
                auto paramValue = placeHolder.getQueryParam<std::string>(param->getName());
                auto rawValues = param->getType().getRaw(paramValue);
                std::copy(std::begin(rawValues), std::end(rawValues), std::back_inserter(cmdParams));
            }

            cluster->executeComand(command, cmdParams);
        } else {
            throwWrongCluster(response, clusterId, endpoint, nwkAddr);
        }
    }

  } /* namespace http */
} /* namespace zigbee */

