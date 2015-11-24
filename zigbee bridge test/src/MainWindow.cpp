/*
 * MainWindow.cpp
 *
 *  Created on: 06/lug/2014
 *      Author: paolo
 */

#include <iostream>

#include "MainWindow.h"
#include "usb/usbConfig.h"
#include "usb/USBDevice.h"
#include "zcl/ZCL.h"
#include "zcl/ClusterTypeFactory.h"
#include "TreeItemSignalMap.h"
#include "QTreeDeviceItem.h"
#include "QTreeWidgetEndpoint.h"
#include "TreeWidgetItem/QTreeBindTableSrc.h"
#include "TreeWidgetItem/TreeWidgetDevice.h"
#include "TreeWidgetItem/TreeWidgetCluster.h"

namespace zigbee {

TreeItemSignalMap TreeItemSignalMap::histance;
std::map<QTreeWidgetItem *, TreeItemSignalMap::itemSignal::slot_type> TreeItemSignalMap::mapSignals;

MainWindow::MainWindow(libusb_context * usbContext) :
		usbContext(usbContext) {

	usbDevice = std::make_shared<USBDevice>(usbContext, USB_CLASS, VENDOR_ID, PRODUCT_ID);
	zigbeeDevice = std::dynamic_pointer_cast<ZigbeeDevice>(usbDevice);

	zigbeeDevice->registerForAnnunceMessage(boost::bind(&MainWindow::annunceDevice, this, _1));
	zigbeeDevice->registerForSimpleDescMessage(boost::bind(&MainWindow::addToGlobalList, this, _1));
	zigbeeDevice->registerForBindTableMessage(boost::bind(&MainWindow::bindTableMsg, this, _1));

	ui.setupUi(this);
	if (zigbeeDevice->isPresent()) {
		zigbeeDevice->requestDevices();
		ui.connectedLED->setState(KLed::On);
	} else {
		ui.connectedLED->setState(KLed::Off);
	}
	timer = new QTimer();

	connect(timer, SIGNAL(timeout()), SLOT(usbPoll()));
	connect(ui.listAllDevices, SIGNAL(itemClicked ( QTreeWidgetItem * , int )), SLOT(allDeviceClick(QTreeWidgetItem * , int )));
	connect(ui.button1, SIGNAL(clicked()), SLOT(generateAnnunce()));
	connect(ui.button2, SIGNAL(clicked()), SLOT(generateSimpleDesc()));
	connect(ui.SimpleDesc, SIGNAL(clicked()), SLOT(requestSimpleDesc()));
	connect(ui.updateBindTableButton, SIGNAL(clicked()), SLOT(updateBindTable()));
	connect(ui.treeButtonDevices, SIGNAL(itemClicked(QTreeWidgetItem *, int )), SLOT(buttonClick(QTreeWidgetItem *, int)));
	connect(ui.treeLightDevices, SIGNAL(itemClicked(QTreeWidgetItem *, int )), SLOT(lightClick(QTreeWidgetItem *, int)));
	connect(ui.bindTable, SIGNAL(itemClicked(QTreeWidgetItem *, int )), SLOT(bindTableClick(QTreeWidgetItem *, int)));
	connect(ui.bindButton, SIGNAL(clicked()), SLOT(bind()));
	timer->start(500);
	ui.bindButton->setEnabled(false);
}


void MainWindow::usbPoll() {
	zigbeeDevice->getUsbMessage();
}

void MainWindow::generateAnnunce() {
	AnnunceMessage annunceMsg;
	annunceMsg.nwkAddr = 1234;
	annunceMsg.extAddr[0] = 1;
	annunceMsg.extAddr[1] = 2;
	annunceMsg.extAddr[2] = 3;
	annunceMsg.extAddr[3] = 4;
	annunceMsg.extAddr[4] = 5;
	annunceMsg.extAddr[5] = 6;
	annunceMsg.extAddr[6] = 7;
	annunceMsg.extAddr[7] = 8;
	annunceDevice(&annunceMsg);
}

void MainWindow::generateSimpleDesc() {
	SimpleDescMessage simpleDescMessage;
	simpleDescMessage.nwkAddr = 1234;
	simpleDescMessage.endpoint = 2;
	simpleDescMessage.appProfId = ZCL_HA_PROFILE_ID;
	simpleDescMessage.appDeviceId = ZCL_HA_DEVICEID_ON_OFF_LIGHT;
	simpleDescMessage.appDevVer = 0;
	simpleDescMessage.numInClusters = 8;
	simpleDescMessage.numOutClusters = 0;
	simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
	simpleDescMessage.clustersList[1] = ClustersId::POWER_CONFIGURATION_CLUSTER;
	simpleDescMessage.clustersList[2] = ClustersId::DEVICE_TEMPERATURE_CONFIG_CLUSTER;
	simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
	simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
	simpleDescMessage.clustersList[5] = ClustersId::SCENE_CLUSTER;
	simpleDescMessage.clustersList[6] = ClustersId::ON_OFF_CLUSTER;
	simpleDescMessage.clustersList[7] = ClustersId::LEVEL_CONTROL;
	simpleDesctMsg(&simpleDescMessage);

	memset(&simpleDescMessage, 0, sizeof(simpleDescMessage));
	simpleDescMessage.nwkAddr = 1234;
	simpleDescMessage.endpoint = 10;
	simpleDescMessage.appProfId = ZCL_HA_PROFILE_ID;
	simpleDescMessage.appDeviceId = ZCL_HA_DEVICEID_ON_OFF_LIGHT;
	simpleDescMessage.appDevVer = 0;
	simpleDescMessage.numInClusters = 8;
	simpleDescMessage.numOutClusters = 0;
	simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
	simpleDescMessage.clustersList[1] = ClustersId::POWER_CONFIGURATION_CLUSTER;
	simpleDescMessage.clustersList[2] = ClustersId::DEVICE_TEMPERATURE_CONFIG_CLUSTER;
	simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
	simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
	simpleDescMessage.clustersList[5] = ClustersId::SCENE_CLUSTER;
	simpleDescMessage.clustersList[6] = ClustersId::ON_OFF_CLUSTER;
	simpleDescMessage.clustersList[7] = ClustersId::LEVEL_CONTROL;
	simpleDesctMsg(&simpleDescMessage);

	memset(&simpleDescMessage, 0, sizeof(simpleDescMessage));
	simpleDescMessage.nwkAddr = 1234;
	simpleDescMessage.endpoint = 12;
	simpleDescMessage.appProfId = ZCL_HA_PROFILE_ID;
	simpleDescMessage.appDeviceId = ZCL_HA_DEVICEID_ON_OFF_SWITCH;
	simpleDescMessage.appDevVer = 0;
	simpleDescMessage.numInClusters = 2;
	simpleDescMessage.numOutClusters = 2;
	simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
	simpleDescMessage.clustersList[1] = ClustersId::POWER_CONFIGURATION_CLUSTER;
	simpleDescMessage.clustersList[2] = ClustersId::IDENTIFY_CLUSTER;
	simpleDescMessage.clustersList[3] = ClustersId::ON_OFF_CLUSTER;
	simpleDesctMsg(&simpleDescMessage);
}

void MainWindow::annunceDevice(AnnunceMessage * annunceMsg) {
	NwkAddr nwkAddr( annunceMsg->nwkAddr );
	if (mapNwkAction.count(nwkAddr) == 0) {
		TreeWidgetDevice * device = new TreeWidgetDevice(ui.listAllDevices, annunceMsg);
		mapNwkAction[nwkAddr] = device;
		ExtAddress extAddress(annunceMsg->extAddr);
		mapAddress[extAddress] = nwkAddr;
	}
}

void MainWindow::requestSimpleDesc() {
	QList<QTreeWidgetItem *> items = ui.listAllDevices->selectedItems();
	for (auto & item : items) {
		for (auto & nwk : mapNwkAction) {
			if (nwk.second == item) {
				usbDevice->requestActiveEndpoints(nwk.first);
			}
		}
	}
}

void MainWindow::addToGlobalList(SimpleDescMessage* simpleDesc) {
	NwkAddr nwkAddr{simpleDesc->nwkAddr};
	if (mapNwkAction.count(nwkAddr) > 0) {
		QTreeWidgetItem* actionParent = mapNwkAction[nwkAddr];
		NkwAddrEndpoint key(nwkAddr, EndpointID{simpleDesc->endpoint});
		if (mapNwkEndpoin_Action.count(key) == 0) {
			QString endpoint = "endpoint: " + QString::number(simpleDesc->endpoint);
			QTreeWidgetItem* itemEndpoint = new QTreeWidgetItem(actionParent);
			itemEndpoint->setText(0, endpoint);
			new QTreeWidgetEndpoint(itemEndpoint, simpleDesc);
			mapNwkEndpoin_Action[key] = itemEndpoint;
			insertInClusters(simpleDesc, itemEndpoint);
		}

		if (simpleDesc->appProfId == ZCL_HA_PROFILE_ID) {
			switch (simpleDesc->appDeviceId) {
				case ZCL_HA_DEVICEID_ON_OFF_LIGHT:
				case ZCL_HA_DEVICEID_DIMMABLE_LIGHT:
				case ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT:
				case ZCL_HA_DEVICEID_ON_OFF_OUTPUT:
				case ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT:
					addToLightdeviceList(simpleDesc);
				break;
				case ZCL_HA_DEVICEID_ON_OFF_SWITCH:
				case ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH:
					addToButtonDeviceList(simpleDesc);
				break;

			}
		}
	}
}

void MainWindow::addToLightdeviceList(SimpleDescMessage* simpleDesc) {
	DeviceKey deviceKey(NwkAddr{simpleDesc->nwkAddr},EndpointID{ simpleDesc->endpoint});
	if (mapLightDeviceAction.count(deviceKey) == 0) {
		QTreeDeviceItem * deviceItem = new QTreeDeviceItem(ui.treeLightDevices, simpleDesc);
		mapLightDeviceAction.insert( { deviceKey, deviceItem });

		ZigbeeClusterId* clusterIds = simpleDesc->clustersList;
		for (int i = 0; i < simpleDesc->numInClusters; i++) {
			QString clusterId = QString::number(*clusterIds);
			std::shared_ptr<Cluster> cluster = ClusterTypeFactory::createCluster(ClusterID{*clusterIds}, zigbeeDevice, EndpointID{simpleDesc->endpoint}, NwkAddr{simpleDesc->nwkAddr});
			new TreeWidgetCluster(deviceItem, cluster);
			clusterIds++;
		}
	}
}

void MainWindow::addToButtonDeviceList(SimpleDescMessage* simpleDesc) {
	DeviceKey deviceKey(NwkAddr{simpleDesc->nwkAddr},EndpointID{ simpleDesc->endpoint});
	if (mapButtonDeviceAction.count(deviceKey) == 0) {
		QTreeDeviceItem * item = new QTreeDeviceItem(ui.treeButtonDevices, simpleDesc);
		mapButtonDeviceAction.insert( { deviceKey, item });
		insertOutClusters(simpleDesc, item);
	}
}

void MainWindow::simpleDesctMsg(SimpleDescMessage * simpleDesc) {
	addToGlobalList(simpleDesc);

}

void MainWindow::allDeviceClick(QTreeWidgetItem * item, int ) {
	TreeItemSignalMap::getHistance().emitSignal(item);
}

void MainWindow::buttonClick(QTreeWidgetItem * item, int ) {
	TreeWidgetCluster * treeWidgetCluster = dynamic_cast<TreeWidgetCluster *>(item);
	if (treeWidgetCluster != nullptr) {

		clusterOut = treeWidgetCluster->getCluster();
		if (clusterOut && clusterIn && clusterIn->getId() == clusterOut->getId()) {
			ui.bindButton->setEnabled(true);
		} else {
			ui.bindButton->setEnabled(false);
		}
	}
}

void MainWindow::lightClick(QTreeWidgetItem * item, int ) {
	TreeWidgetCluster * treeWidgetCluster = dynamic_cast<TreeWidgetCluster *>(item);
	if (treeWidgetCluster != nullptr) {
		clusterIn = treeWidgetCluster->getCluster();
		if (clusterOut && clusterIn && clusterIn->getId() == clusterOut->getId()) {
			ui.bindButton->setEnabled(true);
		} else {
			ui.bindButton->setEnabled(false);
		}
	}
}

void MainWindow::updateBindTable() {
	for (auto buttonDevice : mapButtonDeviceAction) {
		auto deviceKey = buttonDevice.first;
		zigbeeDevice->requestBindTable(std::get<0>(deviceKey));
	}

	auto response1 = std::make_shared<BindTableResponseMessage>();
	response1->dstAddr = 20;
	response1->dstEP = 12;
	response1->clusterID = 13;
	response1->srcAddr[0] = 1;
	response1->srcAddr[1] = 2;
	response1->srcAddr[2] = 3;
	response1->srcAddr[3] = 4;
	response1->srcAddr[4] = 5;
	response1->srcAddr[5] = 6;
	response1->srcAddr[6] = 7;
	response1->srcAddr[7] = 8;
	response1->srcEP = 14;
	bindTableMsg(response1);

	auto response2 = std::make_shared<BindTableResponseMessage>();
	response1->dstAddr = 1234;
	response1->dstEP = 10;
	response1->clusterID = ClustersId::ON_OFF_CLUSTER;
	response1->srcAddr[0] = 1;
	response1->srcAddr[1] = 2;
	response1->srcAddr[2] = 3;
	response1->srcAddr[3] = 4;
	response1->srcAddr[4] = 5;
	response1->srcAddr[5] = 6;
	response1->srcAddr[6] = 7;
	response1->srcAddr[7] = 8;
	response1->srcEP = 12;
	bindTableMsg(response1);
}

void MainWindow::insertInClusters(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem) {
	clustersHandler.insert(simpleDesc, treeItem, zigbeeDevice);
}

void MainWindow::bind() {
//	ZAddrType srcAddr;
//	srcAddr.addrMode = ZAddrType::Addr16Bit;
//	srcAddr.addr.shortAddr = clusterOut->getNetworkAddress().getId();
//
//	ZAddrType dstAddr;
//	dstAddr.addrMode = ZAddrType::Addr16Bit;
//	dstAddr.addr.shortAddr = clusterIn->getNetworkAddress().getId();

	//usbDevice->sendReqBind(clusterOut->getNetworkAddress(), clusterOut, clusterOut->getId(), clusterIn->getNetworkAddress(), clusterIn->getEndpoint());
}

void MainWindow::bindTableMsg(std::shared_ptr<BindTableResponseMessage> bindTable) {
	NwkAddr destAddr{ bindTable->dstAddr};
	EndpointID destEP{ bindTable->dstEP};
	ClusterID clusterId{ bindTable->clusterID};

	BindTableKey key{destAddr, destEP, clusterId};

	if (mapBindTableTree.count(key) == 0) {
		QTreeBindTableDest * dest = new QTreeBindTableDest{ui.bindTable, destAddr, destEP, clusterId};
		mapBindTableTree.insert( { key, dest });
	}

	new QTreeBindTableSrc(mapBindTableTree[key], bindTable->srcAddr, bindTable->srcEP);

}

void MainWindow::bindTableClick(QTreeWidgetItem* item, int ) {

	clearAllSelected(ui.treeButtonDevices);
	clearAllSelected(ui.treeLightDevices);
	QTreeBindTableSrc * bindTableSrc = dynamic_cast<QTreeBindTableSrc *>(item);
	if (bindTableSrc != nullptr) {
		QTreeBindTableDest * dest = (QTreeBindTableDest *) bindTableSrc->parent();
		if (dest != nullptr) {
			ClusterID cluster{dest->getCluster()};
			ExtAddress srcAddr = bindTableSrc->getAddr();
			if (mapAddress.count(srcAddr) > 0) {
				auto shortAddr = mapAddress[srcAddr];
				DeviceKey srcDeviceKey(shortAddr, bindTableSrc->getEndpoint());
				if (mapButtonDeviceAction.count(srcDeviceKey) > 0) {
					QTreeDeviceItem * srcItem = mapButtonDeviceAction[srcDeviceKey];
					srcItem->selectCluster(cluster);
				}
				DeviceKey dstDeviceKey(dest->getAddr(), dest->getEndpoint());
				if (mapLightDeviceAction.count(dstDeviceKey) > 0) {
					QTreeDeviceItem * dstItem = mapLightDeviceAction[dstDeviceKey];
					dstItem->selectCluster(cluster);
				}
			}
		}
	}
}

void MainWindow::insertOutClusters(SimpleDescMessage* simpleDesc, QTreeWidgetItem* treeItem) {
	clustersOutHandler.insert(simpleDesc, treeItem, zigbeeDevice);
}

void MainWindow::clearAllSelected(QTreeWidget* treeWidget) {
	QList<QTreeWidgetItem*> itemsSelected = treeWidget->selectedItems();
	for (QTreeWidgetItem * item : itemsSelected) {
		treeWidget->setItemSelected(item, false);
	}
}

} /* namespace zigbee */
