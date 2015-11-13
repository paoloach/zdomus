/*
 * TreeWidgetCluster.h
 *
 *  Created on: 01/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TREEWIDGETITEM_TREEWIDGETCLUSTER_H_
#define SRC_TREEWIDGETITEM_TREEWIDGETCLUSTER_H_

#include <QtGui/qtreewidget.h>
#include <zcl/Cluster.h>

namespace zigbee {

class TreeWidgetCluster: public QTreeWidgetItem {
public:
	TreeWidgetCluster(QTreeWidgetItem * parent, std::shared_ptr<Cluster> cluster);
	virtual ~TreeWidgetCluster();

	const std::shared_ptr<Cluster> getCluster() const {
		return cluster;
	}

private:
	std::shared_ptr<Cluster> cluster;
};

} /* namespace zigbee */

#endif /* SRC_TREEWIDGETITEM_TREEWIDGETCLUSTER_H_ */
