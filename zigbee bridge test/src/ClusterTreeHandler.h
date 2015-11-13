/*
 * ClusterTreeHandler.h
 *
 *  Created on: 28/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef CLUSTERTREEHANDLER_H_
#define CLUSTERTREEHANDLER_H_

#include <memory>
#include <vector>
#include <QtGui/QTreeWidgetItem>
#include <QtCore/qobject.h>
#include <QtGui/qmenu.h>

#include <zcl/Cluster.h>
#include "AttributeHandler.h"
#include "ui/InsertCmdParams.h"

namespace zigbee {

class Cluster;

class ClusterTreeHandler : public QObject{
	Q_OBJECT
public:
	ClusterTreeHandler(std::shared_ptr<Cluster> cluster);
	virtual ~ClusterTreeHandler();
	bool operator==(const QTreeWidgetItem * widget) const;
public:
	virtual void insert(QTreeWidgetItem * actionCluster);
	std::shared_ptr<Cluster> getCluster() {return cluster;}
protected:
	void createAttributesHandler(std::shared_ptr<Cluster> cluster, QTreeWidgetItem * parentItem);
	void setContextualMenuI( QTreeWidgetItem * parentItem);
	void click();
private slots:
	void cmd();
protected:
	std::vector< std::shared_ptr< AttributeHandler > > attributesHandler;
	std::shared_ptr<Cluster> cluster;
	QTreeWidgetItem * widgeItem;
	QMenu * popupMenu;
	InsertCmdParams insertCmdParams;
};

} /* namespace zigbee */

#endif /* CLUSTERTREEHANDLER_H_ */
