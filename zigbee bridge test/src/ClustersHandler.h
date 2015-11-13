/*
 * ClustersHandler.h
 *
 *  Created on: 11/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_CLUSTERSHANDLER_H_
#define SRC_CLUSTERSHANDLER_H_
#include <vector>
#include <memory>

class QTreeWidgetItem;

namespace zigbee {

class USBDevice;
class Cluster;

class ClustersHandler {
public:
	virtual ~ClustersHandler();
public:
	void push(std::shared_ptr<Cluster>, QTreeWidgetItem* treeItem);
	std::shared_ptr<Cluster> getCluster(QTreeWidgetItem* treeItem);
	void insert(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem, const std::shared_ptr<ZigbeeDevice> & usbDevice);
private:
	std::vector< std::shared_ptr<ClusterTreeHandler> > handlers;
};

} /* namespace zigbee */

#endif /* SRC_CLUSTERSHANDLER_H_ */
