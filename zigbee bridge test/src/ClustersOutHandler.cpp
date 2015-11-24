/*
 * ClustersOutHandler.cpp
 *
 *  Created on: 11/mar/2015
 *      Author: Paolo Achdjian
 */
#include <zcl/ClusterTypeFactory.h>

#include "ClustersOutHandler.h"
#include "TreeWidgetItem/TreeWidgetCluster.h"

namespace zigbee {


void ClustersOutHandler::insert(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem,   std::shared_ptr<ZigbeeDevice> &  usbDevice) {
	ZigbeeClusterId* clusterIds = simpleDesc->clustersList+simpleDesc->numInClusters;
	for (int i = 0; i < simpleDesc->numOutClusters; i++) {
		QString clusterId = QString::number(*clusterIds);
		std::shared_ptr<Cluster> cluster = ClusterTypeFactory::createCluster( ClusterID{*clusterIds}, usbDevice, EndpointID{simpleDesc->endpoint}, NwkAddr{ simpleDesc->nwkAddr});
		new TreeWidgetCluster(treeItem, cluster);
		clusterIds++;
	}
}

} /* namespace zigbee */
