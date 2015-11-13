/*
 * USBDevice.h
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#ifndef USBDEVICE_H_
#define USBDEVICE_H_

#include <boost/signals2.hpp>
#include <map>
#include <boost/asio.hpp>
#include <zigbee/AttributeStatusRecord.h>
#include <zigbee/ZigbeeDevice.h>
#include <zcl/ZCLDataType.h>
#include "../ZigbeeData/ZDevices.h"
#include "../IO/AttributeDataContainer.h"

namespace zigbee {


static const int STANDARD_REQUEST_TYPE { 0 };
static const int CLASS_REQUEST_TYPE { 0x20 };
static const unsigned char VENDOR_REQUEST_TYPE = 0x40;
static const int RESERVED_REQUEST_TYPE { 0x60 };

static const unsigned char REQUEST_DEVICES = 0x20;

class DomusEngioneUSBDevice : public ZigbeeDevice{
private:
	struct AttributeKey {
		AttributeKey(NwkAddr nwkAddress, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attribute) :
				nwkAddr(nwkAddress), endpointId(endpoint), clusterId(cluster), attributeId(attribute) {
		}
		NwkAddr nwkAddr;
		EndpointID endpointId;
		ClusterID clusterId;
		ZigbeeAttributeId attributeId;
		bool operator <(const AttributeKey & otherKey) const;
		bool operator ==(const AttributeKey & otherKey) const;
	};
	BindTableResponseSignal bindTableResponseSignal;
	typedef std::map<AttributeKey, AttributeValueSignal *> AttributeValueSignalMap;
public:
	DomusEngioneUSBDevice(boost::asio::io_service & io, std::shared_ptr<ZDevices> & zDevices, AttributeDataContainer  & attributeDataContainer, libusb_context * usbContext, int deviceClass, int vendorID, int productID);
	virtual ~DomusEngioneUSBDevice();
public:
	bool isPresent() override;
	bool requestDevices() override;
	void getUsbMessage() override;
	void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) override;
	virtual void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen, uint8_t * dataValue) override;
	void sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t>  data = std::vector<uint8_t>()) override;

	boost::signals2::connection registerForAttributeCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeCmdId cmdId,const AttributeCmdSignal::slot_type & subsriber ) override;
	boost::signals2::connection registerForAttributeValue(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
			const AttributeValueSignal::slot_type &subscriber) override;
	virtual boost::signals2::connection registerForAnnunceMessage(const AnnunceSignal::slot_type &subscriber) override;
	virtual boost::signals2::connection registerForSimpleDescMessage(const SimpleDescSignal::slot_type &subscriber) override;
	void requestActiveEndpoints(NwkAddr nwkAddr);

	virtual void sendReqBind(NwkAddr destAddr, uint8_t outClusterAddr[Z_EXTADDR_LEN],EndpointID outClusterEP,ClusterID clusterID, uint8_t inClusterAddr[Z_EXTADDR_LEN],EndpointID inClusterEp) override;
	virtual void requesBindTable(NwkAddr nwkAddrs) override;
	virtual boost::signals2::connection registerForBindTableMessage(const ZigbeeDevice::BindTableResponseSignal::slot_type &subscriber) override;


private:
	boost::asio::io_service & ioService;
	boost::asio::deadline_timer timer;
	libusb_context * usbContext;
	int deviceClass;
	int vendorID;
	int productID;
	libusb_device * device;
	libusb_device_handle * handle;
	AttributeValueSignalMap attributeValueSignalMap;
	std::shared_ptr<ZDevices> zDevices;
	AttributeDataContainer  & attributeDataContainer;

private:
	template<typename T> void sendData(const T & );
	void timerHandler(const boost::system::error_code& error);
	void parseUsbMessage(unsigned char * data, int length);
	void parseAttributeResponse(ReadAttributeResponseMessage * readAttributeResponseMessage);
	std::string strUsbError(int);
};

template<typename T>
inline void zigbee::DomusEngioneUSBDevice::sendData(const T & data) {
	int transfered;

	int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &data, sizeof(data), &transfered, 10);
	if (result == 0) {
		std::cout << "request sent" << std::endl;
	} else {
		std::cerr << strUsbError(result) << std::endl;
	}
}

} /* namespace zigbee */

#endif /* USBDEVICE_H_ */
