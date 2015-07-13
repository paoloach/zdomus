/*
 * QTreeWidgetEndpoint.h
 *
 *  Created on: 25/feb/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_QTREEWIDGETENDPOINT_H_
#define SRC_QTREEWIDGETENDPOINT_H_

#include <QtGui/qtreewidget.h>
#include <zigbee/messageStructure/SimpleDescMessage.h>

namespace zigbee {

class QTreeWidgetEndpoint : public QTreeWidgetItem{
public:
	QTreeWidgetEndpoint (QTreeWidgetItem * parent, const SimpleDescMessage *  simpleDesc);
	virtual ~QTreeWidgetEndpoint(){};
};

} /* namespace zigbee */

#endif /* SRC_QTREEWIDGETENDPOINT_H_ */
