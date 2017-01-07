/*
 * ZEndpointPT.cpp
 *
 *  Created on: 22/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>

#include "ZEndpointPT.h"

namespace zigbee {

using boost::property_tree::ptree;

ZEndpointPT::ZEndpointPT(const ZEndpoint& zEndpoint) noexcept{
	ptree  inCluster;
	ptree outCluster;

	add("short_address", zEndpoint.getNwkAddr().getId());
	add("endpoint_id", zEndpoint.getEndpoint());
	add("profile_id", zEndpoint.getAppProfId());
	add("device_id", zEndpoint.getAppDeviceId());
	add("device_version", zEndpoint.getAppDevVer());
	int index=0;
	for (auto cluster : zEndpoint.getInCluster()) {
		inCluster.add(std::to_string(index), cluster);
		index++;
	}
    if (!inCluster.empty()) {
        push_back({"input_clusters", inCluster});
    }
	index=0;
	for (auto cluster : zEndpoint.getOutCluster()) {
		outCluster.add(std::to_string(index), cluster);
		index++;
	}
    if (!outCluster.empty()) {
        push_back({"output_clusters", outCluster});
    }
}


} /* namespace zigbee */
