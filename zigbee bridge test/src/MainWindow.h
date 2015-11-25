/*
 * MainWindow.h
 *
 *  Created on: 06/lug/2014
 *      Author: paolo
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <libusb.h>
#include <map>

#include <QtGui/QMainWindow>
#include <QtCore/QTimer>
#include <vector>
#include <memory>
#include <tuple>
#include <array>
#include <zigbee/NwkAddr.h>

#include "ClusterTreeHandler.h"
#include "../ui_MainWindow.h"
#include "zcl/Cluster.h"
#include "ClustersHandler.h"
#include "ClustersOutHandler.h"
#include "TreeWidgetItem/QTreeBindTableDest.h"
#include "QTreeDeviceItem.h"
#include "ExtAddress.h"

namespace zigbee {

class ZigbeeDevice;
class USBDevice;

class MainWindow : public QMainWindow{
	Q_OBJECT
	using DeviceKey= std::tuple<NwkAddr, EndpointID>;
	using BindTableKey= std::tuple<NwkAddr, EndpointID, ClusterID>;
public:
	MainWindow(libusb_context * usbContext);
private:
	struct NkwAddrEndpoint {
		NkwAddrEndpoint(NwkAddr nwkAddres,EndpointID endpoint):nwkAddres(nwkAddres),endpoint(endpoint){}
		NwkAddr nwkAddres;
		EndpointID endpoint;

		bool operator<(const NkwAddrEndpoint & other) const {
			return (other.nwkAddres == nwkAddres) ? other.endpoint < endpoint : other.nwkAddres < nwkAddres;
		}
	};
	Ui::MainWindowUI ui;
	libusb_context * usbContext;
	std::shared_ptr<ZigbeeDevice> zigbeeDevice;
	std::shared_ptr<USBDevice> usbDevice;
	QTimer * timer;
	std::shared_ptr<Cluster>  clusterOut;
	std::shared_ptr<Cluster>  clusterIn;
	std::map<NwkAddr, QTreeWidgetItem *> mapNwkAction;
	std::map<DeviceKey, QTreeDeviceItem *> mapLightDeviceAction;
	std::map<DeviceKey, QTreeDeviceItem *> mapButtonDeviceAction;
	std::map<NkwAddrEndpoint, QTreeWidgetItem *> mapNwkEndpoin_Action;
	std::map<BindTableKey, QTreeBindTableDest *> mapBindTableTree;
	std::map<ExtAddress, NwkAddr> mapAddress;

	ClustersHandler clustersHandler;
	ClustersOutHandler clustersOutHandler;

private slots:
	void usbPoll();
	void generateAnnunce();
	void generateSimpleDesc();
	void requestSimpleDesc();
	void updateBindTable();
	void bind();
	void allDeviceClick(QTreeWidgetItem * item , int col );
	void buttonClick(QTreeWidgetItem * item , int col );
	void lightClick(QTreeWidgetItem * item , int col );
	void bindTableClick(QTreeWidgetItem * item , int col );
private: // boot::signal2 slots
	void annunceDevice(AnnunceMessage * annunceMessage);
	void simpleDesctMsg(SimpleDescMessage * annunceMessage);
	void bindTableMsg(std::shared_ptr< BindTableResponseMessage> bindTable);
	void addToGlobalList(SimpleDescMessage* simpleDesc);
	void addToLightdeviceList(SimpleDescMessage* simpleDesc);
	void addToButtonDeviceList(SimpleDescMessage* simpleDesc);
	void insertInClusters(SimpleDescMessage* simpleDesc,QTreeWidgetItem * treeItem);
	void insertOutClusters(SimpleDescMessage* simpleDesc,QTreeWidgetItem * treeItem);
	void clearAllSelected(QTreeWidget * treeWidget);
};

} /* namespace zigbee */

#endif /* MAINWINDOW_H_ */
