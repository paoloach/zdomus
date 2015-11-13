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

	add("short address", zEndpoint.getNwkAddr());
	add("endpoint id", zEndpoint.getEndpoint());
	add("profile id", zEndpoint.getAppProfId());
	add("device id", zEndpoint.getAppDeviceId());
	add("device version", zEndpoint.getAppDevVer());
	int index=0;
	for (auto cluster : zEndpoint.getInCluster()) {
		inCluster.add(boost::lexical_cast<std::string>(index), cluster);
		index++;
	}
	push_back( { "input clusters", inCluster });
	index=0;
	for (auto cluster : zEndpoint.getOutCluster()) {
		outCluster.add(boost::lexical_cast<std::string>(index), cluster);
		index++;
	}
	push_back( { "output clusters", outCluster });
}


} /* namespace zigbee */
