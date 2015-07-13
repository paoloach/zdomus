/*
 * ClustersOutHandler.h
 *
 *  Created on: 11/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_CLUSTERSOUTHANDLER_H_
#define SRC_CLUSTERSOUTHANDLER_H_
#include <vector>
#include <memory>

class QTreeWidgetItem;

namespace zigbee {

class ZigbeeDevice;

class ClustersOutHandler {
public:
	void insert(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem, const std::shared_ptr<ZigbeeDevice> &  usbDevice);
};

} /* namespace zigbee */

#endif /* SRC_CLUSTERSOUTHANDLER_H_ */
