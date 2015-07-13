/*
 * TreeWidgetCluster.cpp
 *
 *  Created on: 01/apr/2015
 *      Author: Paolo Achdjian
 */

#include "TreeWidgetCluster.h"

namespace zigbee {

TreeWidgetCluster::TreeWidgetCluster(QTreeWidgetItem* parent, std::shared_ptr<Cluster> cluster) : QTreeWidgetItem(parent), cluster(cluster) {
	QString clusterName = "cluster: " + QString::number(cluster->getId().getId()) + "(" + QString::fromStdString(cluster->getClusterName()) + ")";
	setText(0,clusterName);
}

TreeWidgetCluster::~TreeWidgetCluster() {
}

} /* namespace zigbee */
