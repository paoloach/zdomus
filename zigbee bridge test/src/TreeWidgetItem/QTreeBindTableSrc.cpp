/*
 * QTreeBindTableSrc.cpp
 *
 *  Created on: 30/mar/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <iomanip>

#include <zigbee/zigbeeConfig.h>

#include "QTreeBindTableSrc.h"

namespace zigbee {

QTreeBindTableSrc::QTreeBindTableSrc(QTreeWidgetItem* parent, uint8_t* srcAddr, int srcEP) : QTreeWidgetItem(parent), addr(srcAddr), endpoint(srcEP){
	std::stringstream stream;

	stream << addr << " - endpoint: "<< std::setfill('0') << std::setw(2) << srcEP;
	setText(0, QString::fromStdString(stream.str()));
}

QTreeBindTableSrc::~QTreeBindTableSrc() {
}

} /* namespace zigbee */
