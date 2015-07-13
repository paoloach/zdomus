/*
 * QTreeDeviceItem.cpp
 *
 *  Created on: 24/feb/2015
 *      Author: Paolo Achdjian
 */

#include "QTreeDeviceItem.h"
#include "TreeWidgetItem/TreeWidgetCluster.h"

namespace zigbee {

QTreeDeviceItem::~QTreeDeviceItem() {
}

QTreeDeviceItem::QTreeDeviceItem(QTreeWidget* parent, const SimpleDescMessage* simpleDesc) :
		QTreeWidgetItem(parent) {
	setText(0, QString::number(simpleDesc->nwkAddr) + ":" + QString::number(simpleDesc->endpoint));
}

} /* namespace zigbee */

void zigbee::QTreeDeviceItem::selectCluster(ClusterID clusterId) {
	treeWidget()->setItemSelected(this, true);
	for (int indexChild = 0; indexChild < childCount(); indexChild++) {
		TreeWidgetCluster * widgetCluster = dynamic_cast<TreeWidgetCluster *>(child(indexChild));
		if (widgetCluster != nullptr) {
			if (widgetCluster->getCluster()->getId() == clusterId) {
				treeWidget()->setItemSelected(this, false);
				treeWidget()->setItemSelected(widgetCluster, true);
				treeWidget()->expandItem(this);
			}
		}

	}
}
