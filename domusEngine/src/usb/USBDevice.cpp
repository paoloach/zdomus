/*
 * USBDevice.cpp
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#include <iostream>
#include <iomanip>
#include <libusb-1.0/libusb.h>
#include <boost/bind.hpp>
#include "usbConfig.h"
#include "USBDevice.h"

#include "zigbee/messageStructure/AnnunceMessage.h"
#include "zigbee/messageStructure/ReqActiveEndpointsMessage.h"
#include "zigbee/messageStructure/SimpleDescMessage.h"
#include "zigbee/messageStructure/ReadAttributeResponseMessage.h"
#include "zigbee/messageStructure/AttributeValue.h"
#include "zigbee/messageStructure/ComandSend.h"
#include "zigbee/messageStructure/WriteAttributeValue.h"
#include "zigbee/messageStructure/BindTableResponseMessage.h"
#include "zigbee/messageStructure/BindRequest.h"

namespace zigbee {

static const boost::posix_time::time_duration CHECK_NEW_MESSAGE = boost::posix_time::seconds(1);

DomusEngioneUSBDevice::DomusEngioneUSBDevice(boost::asio::io_service & serviceIo_, std::shared_ptr<ZDevices> & zDevices_, AttributeDataContainer & attributeDataContainer_,
        libusb_context * usbContext_, int deviceClass_, int vendor_, int product_) :
		ioService(serviceIo_), timer(serviceIo_, CHECK_NEW_MESSAGE), usbContext(usbContext_), deviceClass { deviceClass_ }, vendorID { vendor_ }, productID { product_ }, handle(
		        nullptr), zDevices(zDevices_), attributeDataContainer(attributeDataContainer_) {
	device = nullptr;
	timer.async_wait(boost::bind(&DomusEngioneUSBDevice::timerHandler, this, boost::asio::placeholders::error));
}

DomusEngioneUSBDevice::~DomusEngioneUSBDevice() {
	for (auto & element : attributeValueSignalMap) {
		delete element.second;
	}
}

void DomusEngioneUSBDevice::timerHandler(const boost::system::error_code&) {
	if (isPresent()) {
		getUsbMessage();
	}
	timer.expires_from_now(CHECK_NEW_MESSAGE);
	timer.async_wait(boost::bind(&DomusEngioneUSBDevice::timerHandler, this, boost::asio::placeholders::error));
}

void emptySlot(void) {

}

std::string DomusEngioneUSBDevice::strUsbError(int error) {
	switch (error) {
		case LIBUSB_ERROR_IO:
			return "input/output error";
		case LIBUSB_ERROR_TIMEOUT:
			return "timeout error";
		case LIBUSB_ERROR_NOT_FOUND:
			return "error not found";
		case LIBUSB_ERROR_PIPE:
			return "the endpoint halted";
		case LIBUSB_ERROR_OVERFLOW:
			return "The device offered more data";
		case LIBUSB_ERROR_NO_DEVICE:
			return "the device has been disconnected";
		case LIBUSB_ERROR_BUSY:
			return "resouce busy";
		default:
			return "unknow usb error: ";
	}
}

/**
 * find in the usb tree if the device is present
 */
bool DomusEngioneUSBDevice::isPresent() {
	if (device != nullptr) {
		return true;
	} else {
		libusb_device **devices { };

		handle = NULL;
		ssize_t devicesNum = libusb_get_device_list((libusb_context *) usbContext, &devices);

		for (int index = 0; index < devicesNum; index++) {
			libusb_device_descriptor deviceDescriptor;
			libusb_get_device_descriptor(devices[index], &deviceDescriptor);
			if (deviceDescriptor.bDeviceClass == deviceClass && deviceDescriptor.idVendor == vendorID && deviceDescriptor.idProduct == productID) {
				device = devices[index];
				libusb_ref_device((libusb_device*) device);
				int result = libusb_open((libusb_device*) device, (libusb_device_handle**) &handle);
				if (result != 0) {
					std::cerr << "Unable to open device: " << strUsbError(result) << std::endl;
					return false;
				}
				break;
			}
		}
		libusb_free_device_list(devices, 1);
		if (handle != NULL) {
			std::cout << "device found" << std::endl;
			int result = libusb_claim_interface((libusb_device_handle*) handle, 0);
			if (result != 0) {
				std::cerr << "Unable to claim interface 0: " << strUsbError(result) << std::endl;
			}
		} else {
			std::cerr << "device not found" << std::endl;
		}
	}
	return device != nullptr;
}

/**
 * Check if there is a message from the usb device and emit the right sihnal
 */
void DomusEngioneUSBDevice::getUsbMessage() {
	unsigned char data[64] { };
	int transfered { };
	if (device) {
		int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_IN, data, sizeof(data), &transfered, 10);
		if (result == 0) {
			std::cout << "new data arrived: size " << transfered << std::endl;
			std::cout << "data: ";
			for (int i = 0; i < transfered; i++) {
				std::cout << (int) data[i] << " - ";
			}
			std::cout << std::endl;
			parseUsbMessage(data, transfered);
		} else if (result == LIBUSB_ERROR_TIMEOUT) {
			// no data
		} else {
			std::cerr << strUsbError(result) << std::endl;
		}
	}
}

void DomusEngioneUSBDevice::parseUsbMessage(unsigned char * data, int length) {
	AnnunceMessage *annunceMessage { };
	SimpleDescMessage *simpleDescMessage { };
	ReadAttributeResponseMessage *readAttributeResponseMessage { };
	if (length > 0) {
		switch (*data) {
			case ANNUNCE_MSG:
				annunceMessage = (AnnunceMessage *) data;
				zDevices->put(*annunceMessage);
				std::cout << "Annunce signal" << std::endl;
				requestActiveEndpoints(NwkAddr(annunceMessage->nwkAddr));
			break;
			case SIMPLE_DESC:
				simpleDescMessage = (SimpleDescMessage *) data;
				zDevices->put(*simpleDescMessage);
				std::cout << "Simple desciption message " << std::endl;
			break;
			case ATTRIBUTE_VALUES:
				std::cout << "Read response attribute value" << std::endl;
				readAttributeResponseMessage = (ReadAttributeResponseMessage *) data;
				for (unsigned int i = 0; i < sizeof(ReadAttributeResponseMessage); i++) {
					std::cout << (int) (data[i]) << " - ";
				}
				std::cout << std::endl;
				std::cout << "data len: " << (int) readAttributeResponseMessage->dataLen << std::endl;
				attributeDataContainer.push(*readAttributeResponseMessage);
			break;

		}
	}
}

void DomusEngioneUSBDevice::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) {
	std::cout << "USBDevice request device (" << nwkAddrs << ", " << endpoint << ", " << cluster << ", " << attributeId << ")" << std::endl;
	if (handle != nullptr) {
		AttributeValue attributeValue { };
		attributeValue.nwkAddr = nwkAddrs.getId();
		attributeValue.endpoint = endpoint.getId();
		attributeValue.cluster = cluster.getId();
		attributeValue.attribute = attributeId;

		int transfered { };
		std::cout << "request attribute: ";
		for (unsigned int i = 0; i < sizeof(attributeValue); i++) {
			std::cout << (int) (*((unsigned char *) &attributeValue + i)) << " - ";
		}
		int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &attributeValue, sizeof(attributeValue), &transfered, 10);
		if (result == 0) {
			std::cout << "request sent" << std::endl;
		} else {
			std::cerr << strUsbError(result) << std::endl;
		}
	}
}

void DomusEngioneUSBDevice::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attrId, ZCLTypeDataType dataType, uint8_t dataValueLen,
        uint8_t * dataValue) {
	std::cout << "USBDevice write attribute to cluster " << std::endl;
	if (handle != nullptr) {
		WriteAttributeValueMsg writeAttributeValue { };

		writeAttributeValue.nwkAddr = nwkAddrs.getId();
		writeAttributeValue.endpoint = endpoint.getId();
		writeAttributeValue.cluster = cluster.getId();
		writeAttributeValue.attributeId = attrId;
		writeAttributeValue.dataType = static_cast<ZigbeeAttributeDataType>(dataType);
		writeAttributeValue.dataValueLen = dataValueLen;
		memcpy(writeAttributeValue.dataValue, dataValue, dataValueLen);
		int transfered { };
		int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &writeAttributeValue, sizeof(WriteAttributeValueMsg), &transfered,
		        10);
		if (result == 0) {
			std::cout << "request sent" << std::endl;
		} else {
			std::cerr << strUsbError(result) << std::endl;
		}
	}
}

void DomusEngioneUSBDevice::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId comandId, std::vector<uint8_t> data) {
	std::cout << "USBDevice send cmd to cluster (" << nwkAddrs << ", " << endpoint << ", " << cluster << ", " << comandId << ")" << std::endl;
	if (handle != nullptr) {
		ComandSend comandSend { nwkAddrs, endpoint, cluster, comandId, data };

		int transfered { };
		int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &comandSend, sizeof(comandSend), &transfered, 10);
		if (result == 0) {
			std::cout << "request sent" << std::endl;
		} else {
			std::cerr << strUsbError(result) << std::endl;
		}
	}
}

void DomusEngioneUSBDevice::parseAttributeResponse(ReadAttributeResponseMessage * readAttributeResponseMessage) {
	AttributeKey key(NwkAddr(readAttributeResponseMessage->networkAddr), EndpointID(readAttributeResponseMessage->endpoint), ClusterID(readAttributeResponseMessage->clusterId),
	        readAttributeResponseMessage->attrID);
	auto found = attributeValueSignalMap.find(key);
	if (found != attributeValueSignalMap.end()) {
		std::shared_ptr<AttributeStatusRecord> attributeStatus = std::make_shared<AttributeStatusRecord>();
		attributeStatus->attributeId = readAttributeResponseMessage->attrID;
		attributeStatus->attributeDataType = readAttributeResponseMessage->type;
		attributeStatus->status = readAttributeResponseMessage->status;
		attributeStatus->dataLen = readAttributeResponseMessage->dataLen;
		memcpy(attributeStatus->data, readAttributeResponseMessage->data, attributeStatus->dataLen);
		AttributeValueSignal & signal = *found->second;
		signal(attributeStatus);
	}
}

boost::signals2::connection DomusEngioneUSBDevice::registerForAttributeValue(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
        const AttributeValueSignal::slot_type &subscriber) {
	AttributeValueSignal *signal { };
	AttributeKey key(nwkAddrs, endpoint, cluster, attributeId);
	auto found = attributeValueSignalMap.find(key);
	if (found != attributeValueSignalMap.end()) {
		signal = found->second;
		signal->disconnect_all_slots();
	} else {
		signal = new AttributeValueSignal { };
		attributeValueSignalMap[key] = signal;
	}
	return signal->connect(subscriber);
}

/**
 * send request devices
 */
bool DomusEngioneUSBDevice::requestDevices() {
	int transfered;
	GenericMessage genericMessage;

	genericMessage.msgCode = REQ_ALL_NODES;
	int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &genericMessage, sizeof(genericMessage), &transfered, 10);
	if (result == 0) {
		std::cout << "request sent" << std::endl;
	} else {
		std::cerr << strUsbError(result) << std::endl;
	}
	return false;
}

void DomusEngioneUSBDevice::requestActiveEndpoints(NwkAddr nwkAddr) {
	ReqActiveEndpointsMessage request { };
	request.nwkAddr = nwkAddr.getId();

	int transfered { };

	int result = libusb_bulk_transfer((libusb_device_handle*) handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request), &transfered, 10);
	if (result == 0) {
		std::cout << "request sent" << std::endl;
	} else {
		std::cerr << strUsbError(result) << std::endl;
	}
}

boost::signals2::connection DomusEngioneUSBDevice::registerForAttributeCmd(NwkAddr, EndpointID, ClusterID, ZigbeeAttributeCmdId, const AttributeCmdSignal::slot_type &) {
	return boost::signals2::connection { };
}

bool DomusEngioneUSBDevice::AttributeKey::operator <(const AttributeKey & otherKey) const {
	if (nwkAddr == otherKey.nwkAddr) {
		if (endpointId == otherKey.endpointId) {
			if (clusterId == otherKey.clusterId) {
				return attributeId < otherKey.attributeId;
			} else {
				return clusterId < otherKey.clusterId;
			}
		} else {
			return endpointId < otherKey.endpointId;
		}
	} else {
		return nwkAddr < otherKey.nwkAddr;
	}
}

bool DomusEngioneUSBDevice::AttributeKey::operator ==(const AttributeKey & otherKey) const {
	return otherKey.nwkAddr == nwkAddr && otherKey.endpointId == endpointId && otherKey.clusterId == clusterId && otherKey.attributeId == attributeId;
}

void parseAttributeResponse(ReadAttributeResponseMessage *) {

}

boost::signals2::connection DomusEngioneUSBDevice::registerForAnnunceMessage(const AnnunceSignal::slot_type &) {
	return boost::signals2::connection { };
}
boost::signals2::connection DomusEngioneUSBDevice::registerForSimpleDescMessage(const SimpleDescSignal::slot_type &) {
	return boost::signals2::connection { };
}

void DomusEngioneUSBDevice::sendReqBind(NwkAddr destAddr, uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, uint8_t inClusterAddr[Z_EXTADDR_LEN],
        EndpointID inClusterEp) {
	BindRequest bindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);

	sendData(bindRequest);
}
void DomusEngioneUSBDevice::requesBindTable(NwkAddr) {

}

boost::signals2::connection DomusEngioneUSBDevice::registerForBindTableMessage(const ZigbeeDevice::BindTableResponseSignal::slot_type &subscriber) {
	return bindTableResponseSignal.connect(subscriber);
}

} /* namespace zigbee */
