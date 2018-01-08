/*
 * ClusterPT.h
 *
 *  Created on: 28/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_PROPERTYTREE_CLUSTERPT_H_
#define SRC_ZIGBEEDATA_PROPERTYTREE_CLUSTERPT_H_

#include <boost/property_tree/ptree.hpp>
#include <zcl/Cluster.h>
#include <memory>

namespace zigbee {

class ClusterPT  : public boost::property_tree::ptree{
public:
	ClusterPT(const Cluster * cluster) noexcept;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_PROPERTYTREE_CLUSTERPT_H_ */
