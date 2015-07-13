/*
 * TreeWidgetDevice.h
 *
 *  Created on: 31/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TREEWIDGETITEM_TREEWIDGETDEVICE_H_
#define SRC_TREEWIDGETITEM_TREEWIDGETDEVICE_H_

#include <QtGui/qtreewidget.h>
#include <zigbee/messageStructure/AnnunceMessage.h>

namespace zigbee {

class TreeWidgetDevice: public QTreeWidgetItem  {
public:
	TreeWidgetDevice(QTreeWidget* parent, AnnunceMessage *);
	virtual ~TreeWidgetDevice();
};

} /* namespace zigbee */

#endif /* SRC_TREEWIDGETITEM_TREEWIDGETDEVICE_H_ */
