/*
 * ExecuteCmd.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */


#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "ExecuteCmd.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ExecuteCmd::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter  && response) {
            BOOST_LOG_TRIVIAL(info) << "ExecuteCmd";

            auto nwkAddr = request.param(":device").as<NwkAddr>();
            auto endpoint = request.param(":endpoint").as<EndpointID>();
            auto clusterId = request.param(":cluster").as<ClusterID>();
            auto command = request.param(":command").as<int>();
            auto zDevice = singletons.getZDevices()->getDevice(nwkAddr);
            auto zEndpoint = zDevice->getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
            if (zEndpoint.isInCluster(clusterId)) {
                std::vector<uint8_t> cmdParams{};
                response.send(Code::No_Content, "command sent\n\r");
                auto cluster(singletons.getClusters()->getCluster(nwkAddr, endpoint, clusterId));

                auto params = cluster->getCmdParams(command);
                for (const auto &param : params) {
                    auto paramValue = request.query().get(param->getName());
                    if (!paramValue.isEmpty()) {
                        auto rawValues = param->getType().getRaw(paramValue.get());
                        std::copy(std::begin(rawValues), std::end(rawValues), std::back_inserter(cmdParams));
                    }
                }

                cluster->executeComand(command, cmdParams);
            } else {
                BOOST_LOG_TRIVIAL(error) << "Available in clusters are";
                for (auto &inCluster: zEndpoint.getInCluster()) {
                    BOOST_LOG_TRIVIAL(error) << inCluster.getId();
                }
                throwWrongCluster(std::move(response), clusterId, endpoint, nwkAddr);
            }
            return Net::Rest::Route::Result::Ok;
        }

    } /* namespace http */
} /* namespace zigbee */

