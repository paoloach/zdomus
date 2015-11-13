/*
 * TreeItemSignalMap.cpp
 *
 *  Created on: 01/ago/2014
 *      Author: Paolo Achdjian
 */

#include "TreeItemSignalMap.h"

namespace zigbee {


TreeItemSignalMap::~TreeItemSignalMap() {
}

void TreeItemSignalMap::add(QTreeWidgetItem * item, itemSignal::slot_type subscriber) {
	mapSignals.insert(MapSignals::value_type(item, subscriber));
}

void TreeItemSignalMap::emitSignal(QTreeWidgetItem * item){
	auto found = mapSignals.find(item);
	if (found != mapSignals.end()){
		found->second();
	}
}

} /* namespace zigbee */
