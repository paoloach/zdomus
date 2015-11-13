/*
 * QTreeDeviceItem.h
 *
 *  Created on: 24/feb/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_QTREEDEVICEITEM_H_
#define SRC_QTREEDEVICEITEM_H_

#include <zigbee/ClusterID.h>
#include <QtGui/qtreewidget.h>
#include <zigbee/messageStructure/SimpleDescMessage.h>

namespace zigbee {

class QTreeDeviceItem : public QTreeWidgetItem{
public:
	virtual ~QTreeDeviceItem();
	QTreeDeviceItem(QTreeWidget * parent, const SimpleDescMessage *  simpleDesc );
	void selectCluster(ClusterID clusterId);
};

} /* namespace zigbee */

#endif /* SRC_QTREEDEVICEITEM_H_ */
