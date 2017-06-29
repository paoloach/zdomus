/*
 * ClusterThrowingException.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zigbee/EndpointID.h>
#include <iostream>
#include <boost/log/trivial.hpp>

#include "ClusterThrowingException.h"

namespace zigbee {
    namespace http {

        void ClusterThrowingException::throwWrongCluster(Net::Http::ResponseWriter &&response, const ClusterID &clusterId, const EndpointID &endpointId, const NwkAddr &nwkAddr) {
            std::stringstream message;

            message << "ERROR: " << "cluster " << clusterId << " is not an IN cluster of endpoint " << endpointId << " in the device with address " << nwkAddr << "\n";
            BOOST_LOG_TRIVIAL(error) << message.str() << std::endl;
            response.send(Net::Http::Code::Bad_Request, message.str());

        }

    } /* namespace http */
} /* namespace zigbee */

