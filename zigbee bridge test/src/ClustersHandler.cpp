/*
 * ClustersHandler.cpp
 *
 *  Created on: 11/mar/2015
 *      Author: Paolo Achdjian
 */

#include <zcl/ClusterTypeFactory.h>
#include <zcl/Cluster.h>

#include "ClusterTreeHandler.h"
#include "ClustersHandler.h"

namespace zigbee {

ClustersHandler::~ClustersHandler() {
}

void ClustersHandler::push(std::shared_ptr<Cluster> cluster, QTreeWidgetItem* treeItem) {
	std::shared_ptr<ClusterTreeHandler> clusterHandler = std::make_shared<ClusterTreeHandler>(cluster);
	clusterHandler->insert(treeItem);
	handlers.push_back(clusterHandler);
}

std::shared_ptr<Cluster> ClustersHandler::getCluster(QTreeWidgetItem* treeItem) {
	for (auto clusterHandler : handlers) {
		if (*clusterHandler == treeItem) {
			return clusterHandler->getCluster();
		}
	}
	return std::shared_ptr<Cluster>();
}

void ClustersHandler::insert(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem, std::shared_ptr<ZigbeeDevice> & usbDevice) {
	ZigbeeClusterId* clusterIds = simpleDesc->clustersList;
	for (int i = 0; i < simpleDesc->numInClusters; i++) {
		QString clusterId = QString::number(*clusterIds);
		std::shared_ptr<Cluster> cluster = ClusterTypeFactory::createCluster(ClusterID { *clusterIds }, usbDevice, EndpointID { simpleDesc->endpoint },
				NwkAddr { simpleDesc->nwkAddr });
		push(cluster, treeItem);
		clusterIds++;
	}
}

} /* namespace zigbee */
