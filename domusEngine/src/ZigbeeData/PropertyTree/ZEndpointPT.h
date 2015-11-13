/*
 * ZEndpointPT.h
 *
 *  Created on: 22/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_PROPERTYTREE_ZENDPOINTPT_H_
#define SRC_ZIGBEEDATA_PROPERTYTREE_ZENDPOINTPT_H_

#include <boost/property_tree/ptree.hpp>
#include "../ZEndpoint.h"

namespace zigbee {

class ZEndpointPT : public boost::property_tree::ptree{
public:
	ZEndpointPT(const ZEndpoint & zEndpoint) noexcept;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_PROPERTYTREE_ZENDPOINTPT_H_ */
