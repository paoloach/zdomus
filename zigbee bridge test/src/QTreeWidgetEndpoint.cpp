/*
 * QTreeWidgetEndpoint.cpp
 *
 *  Created on: 25/feb/2015
 *      Author: Paolo Achdjian
 */

#include "QTreeWidgetEndpoint.h"

namespace zigbee {

QTreeWidgetEndpoint::QTreeWidgetEndpoint(QTreeWidgetItem * parent, const SimpleDescMessage *  simpleDesc): QTreeWidgetItem(parent) {
	setText(0, "configurations");
	QTreeWidgetItem * profileId = new QTreeWidgetItem(this);
	profileId->setText(0, "Profile ID = " + QString::number(simpleDesc->appProfId));

	QTreeWidgetItem * deviceId = new QTreeWidgetItem(this);
	deviceId->setText(0, "Device ID = " + QString::number(simpleDesc->appDeviceId));

	QTreeWidgetItem * deviceVer = new QTreeWidgetItem(this);
	deviceVer->setText(0, "Device Version = " + QString::number(simpleDesc->appDevVer & 0x0F));
	int flags = (simpleDesc->appDevVer & 0xF0) >> 4;
	QTreeWidgetItem * complexDesc = new QTreeWidgetItem(this);
	QString available = (flags & 0x2) ? "available" : "not available";
	complexDesc->setText(0, QString("Complex description ") + available);

	QTreeWidgetItem * userDesc = new QTreeWidgetItem(this);
	available = (flags & 0x2) ? "available" : "not available";
	userDesc->setText(0, QString("User description ") + available);
}

} /* namespace zigbee */
