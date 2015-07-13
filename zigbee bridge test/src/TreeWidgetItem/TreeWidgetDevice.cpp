/*
 * TreeWidgetDevice.cpp
 *
 *  Created on: 31/mar/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>

#include "TreeWidgetDevice.h"
#include "../ExtAddress.h"

namespace zigbee {

TreeWidgetDevice::TreeWidgetDevice(QTreeWidget* parent, AnnunceMessage* annunceMessage): QTreeWidgetItem(parent) {
	int nwkAddr = annunceMessage->nwkAddr;
	setText(0, QString::number(nwkAddr));
	ExtAddress extAddress(annunceMessage->extAddr);

	std::stringstream stream;

	stream << extAddress;
	setToolTip(0, QString::fromStdString(stream.str()));
}

TreeWidgetDevice::~TreeWidgetDevice() {
}

} /* namespace zigbee */
