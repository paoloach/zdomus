/*
 * TreeItemSignalMap.h
 *
 *  Created on: 01/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef TREEITEMSIGNALMAP_H_
#define TREEITEMSIGNALMAP_H_

#include <map>
#include <boost/signals2.hpp>
#include <QtGui/QTreeWidgetItem>

namespace zigbee {

class TreeItemSignalMap {
public:
	typedef boost::signals2::signal<void(void)> itemSignal;
	virtual ~TreeItemSignalMap();
	static TreeItemSignalMap & getHistance(){return histance;}
	TreeItemSignalMap(){}
public:
	void add(QTreeWidgetItem * item, itemSignal::slot_type subscriber);
	void emitSignal(QTreeWidgetItem * item);
private:
	TreeItemSignalMap(TreeItemSignalMap &){}
private:
	typedef std::map<QTreeWidgetItem *, itemSignal::slot_type > MapSignals;
	static TreeItemSignalMap histance;
	static MapSignals mapSignals;

};

} /* namespace zigbee */

#endif /* TREEITEMSIGNALMAP_H_ */
