/*
 * QTreeBindTableDest.cpp
 *
 *  Created on: 27/mar/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <QtGui/qtreewidget.h>

#include "QTreeBindTableDest.h"

namespace zigbee {

QTreeBindTableDest::QTreeBindTableDest(QTreeWidget* parent, NwkAddr destAddr, EndpointID destEP, ClusterID destCluster) : QTreeWidgetItem(parent) , addr(destAddr), endpoint(destEP), cluster(destCluster){
	std::stringstream stream;

	stream << destAddr << ":" << destEP << ":" << destCluster;

	setText(0, QString::fromStdString(stream.str()));
}

QTreeBindTableDest::~QTreeBindTableDest() {
}

} /* namespace zigbee */
