/*
 * USBDevice.cpp
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#include <iostream>
#include <iomanip>
#include <libusb-1.0/libusb.h>
#include "usbConfig.h"
#include "USBDevice.h"
#include "zigbee/messageStructure/AnnunceMessage.h"
#include "zigbee/messageStructure/ReqActiveEndpointsMessage.h"
#include "zigbee/messageStructure/SimpleDescMessage.h"
#include "zigbee/messageStructure/ReadAttributeResponseMessage.h"
#include "zigbee/messageStructure/AttributeValue.h"
#include "zigbee/messageStructure/ComandSend.h"
#include "zigbee/messageStructure/WriteAttributeValue.h"
#include "zigbee/messageStructure/ReqBindTable.h"
#include "zigbee/messageStructure/BindRequest.h"

namespace zigbee {

  USBDevice::USBDevice(libusb_context *usbContext, int deviceClass, int vendorID, int idProduct) :
          usbContext(usbContext), deviceClass{deviceClass}, vendorID{vendorID}, productID{idProduct}, device(nullptr), handle(nullptr) {

  }

  void emptySlot(void) {

  }

  std::string USBDevice::strUsbError(int error) {
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
  bool USBDevice::isPresent() {
      libusb_device **devices;
      device = NULL;
      handle = NULL;
      ssize_t devicesNum = libusb_get_device_list((libusb_context *) usbContext, &devices);

      for (int index = 0; index < devicesNum; index++) {
          libusb_device_descriptor deviceDescriptor;
          libusb_get_device_descriptor(devices[index], &deviceDescriptor);
          if (deviceDescriptor.bDeviceClass == deviceClass && deviceDescriptor.idVendor == vendorID && deviceDescriptor.idProduct == productID) {
              device = devices[index];
              libusb_ref_device((libusb_device *) device);
              int result = libusb_open((libusb_device *) device, (libusb_device_handle **) &handle);
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
          int result = libusb_claim_interface((libusb_device_handle *) handle, 0);
          if (result != 0) {
              std::cerr << "Unable to claim interface 0: " << strUsbError(result) << std::endl;
          }
      } else {
          std::cerr << "device not found" << std::endl;
      }
      return device != NULL;
  }

/**
 * Check if there is a message from the usb device and emit the right sihnal
 */
  void USBDevice::getUsbMessage() {
      unsigned char data[64];
      int transfered;
      if (device != nullptr) {
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_IN, data, sizeof(data), &transfered, 10);
          if (result == 0) {
              std::cout << "new data arrived" << std::endl;
              parseUsbMessage(data, transfered);
          } else if (result == LIBUSB_ERROR_TIMEOUT) {
              // no data
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void USBDevice::parseUsbMessage(unsigned char *data, int length) {
      AnnunceMessage *annunceMessage;
      SimpleDescMessage *simpleDescMessage;
      ReadAttributeResponseMessage *readAttributeResponseMessage;
      BindTableResponseMessage *bindTableResponseMessage;
      if (length > 0) {
          switch (*data) {
              case ANNUNCE_MSG:
                  annunceMessage = (AnnunceMessage *) data;
                  std::cout << "Annunce signal" << std::endl;
                  memcpy(addrLookup[NwkAddr(annunceMessage->nwkAddr)], annunceMessage->extAddr, Z_EXTADDR_LEN);
                  std::for_each(annunceSignal.begin(), annunceSignal.end(), [annunceMessage](AnnunceCallback &callback) { callback(annunceMessage); });
                  requestActiveEndpoints(NwkAddr(annunceMessage->nwkAddr));
                  break;
              case SIMPLE_DESC:
                  simpleDescMessage = (SimpleDescMessage *) data;
                  std::for_each(simpleDescSignal.begin(), simpleDescSignal.end(), [simpleDescMessage](SimpleDescCallback &callback) { callback(simpleDescMessage); });
                  std::cout << "Simple desciption message " << std::endl;
                  break;
              case ATTRIBUTE_VALUES:
                  std::cout << "Read response attribute value" << std::endl;
                  readAttributeResponseMessage = (ReadAttributeResponseMessage *) data;
                  for (int i = 0; i < sizeof(ReadAttributeResponseMessage); i++) {
                      std::cout << std::hex << (int) data[i] << " - ";
                  }
                  std::cout << std::endl;
                  std::cout << "data len: " << (int) readAttributeResponseMessage->dataLen << std::endl;
                  parseAttributeResponse(readAttributeResponseMessage);
                  break;
              case BIND_TABLE:
                  std::cout << "Bind table entry" << std::endl;
                  bindTableResponseMessage = (BindTableResponseMessage *) data;
                  auto dataToSend = std::make_shared<BindTableResponseMessage>(*bindTableResponseMessage);
                  std::for_each(bindTableResponseSignal.begin(), bindTableResponseSignal.end(), [dataToSend](BindTableResponseCallback &callback) { callback(dataToSend); });
                  break;
          }
      }
  }

  void USBDevice::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) {
      std::cout << "USBDevice request device " << std::endl;
      if (handle != nullptr) {
          AttributeValue attributeValue{nwkAddrs, endpoint, cluster, attributeId};

          int transfered;
          for (int i = 0; i < sizeof(attributeValue); i++) {
              std::cout << (int) (*((unsigned char *) &attributeValue + i)) << " - ";
          }
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &attributeValue, sizeof(attributeValue), &transfered, 10);
          if (result == 0) {
              std::cout << "request sent" << std::endl;
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void USBDevice::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attrId, ZCLTypeDataType dataType,
                                 uint8_t dataValueLen, uint8_t *dataValue) {
      std::cout << "USBDevice write attribute to cluster " << std::endl;
      if (handle != nullptr) {
          WriteAttributeValueMsg writeAttributeValue(nwkAddrs, endpoint, cluster, attrId, dataType, dataValueLen, dataValue);

          int transfered;
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &writeAttributeValue, sizeof(WriteAttributeValueMsg),
                                            &transfered,
                                            10);
          if (result == 0) {
              std::cout << "request sent" << std::endl;
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void USBDevice::sendCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId comandId, std::vector<uint8_t> data) {
      std::cout << "USBDevice send cmd to cluster " << std::endl;
      if (handle != nullptr) {
          ComandSend comandSend{nwkAddrs, endpoint, cluster, comandId, data};

          int transfered;
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &comandSend, sizeof(comandSend), &transfered, 10);
          if (result == 0) {
              std::cout << "request sent" << std::endl;
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void USBDevice::parseAttributeResponse(ReadAttributeResponseMessage *readAttributeResponseMessage) {
      AttributeKey key(NwkAddr(readAttributeResponseMessage->networkAddr), readAttributeResponseMessage->endpoint, readAttributeResponseMessage->clusterId,
                       readAttributeResponseMessage->attrID);
      auto found = attributeValueSignalMap.equal_range(key);
      if (found.first != attributeValueSignalMap.end()) {
          std::shared_ptr<AttributeStatusRecord> attributeStatus = std::make_shared<AttributeStatusRecord>();
          attributeStatus->attributeId = readAttributeResponseMessage->attrID;
          attributeStatus->attributeDataType = readAttributeResponseMessage->type;
          attributeStatus->status = readAttributeResponseMessage->status;
          attributeStatus->dataLen = readAttributeResponseMessage->dataLen;

          memcpy(attributeStatus->data, readAttributeResponseMessage->data, attributeStatus->dataLen);
          std::for_each(found.first, found.second, [&attributeStatus](AttributeValueSignalMap::value_type &callback) { callback.second(attributeStatus); });
      }
  }


/**
 * send request devices
 */
  bool USBDevice::requestDevices() {
      int transfered;
      GenericMessage genericMessage;

      genericMessage.msgCode = REQ_ALL_NODES;
      int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &genericMessage, sizeof(genericMessage), &transfered, 10);
      if (result == 0) {
          std::cout << "request sent" << std::endl;
      } else {
          std::cerr << strUsbError(result) << std::endl;
      }
      return false;
  }

  void USBDevice::requestActiveEndpoints(NwkAddr nwkAddr) {
      ReqActiveEndpointsMessage request;
      request.nwkAddr = nwkAddr.getId();

      int transfered;

      int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request), &transfered, 10);
      if (result == 0) {
          std::cout << "request sent" << std::endl;
      } else {
          std::cerr << strUsbError(result) << std::endl;
      }
  }

  void USBDevice::requestBindTable(NwkAddr nwkAddrs) {
      ReqBindTable request(nwkAddrs.getId());
      sendData(request);
  }

  bool USBDevice::AttributeKey::operator<(const AttributeKey &otherKey) const {
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

  bool USBDevice::AttributeKey::operator==(const AttributeKey &otherKey) const {
      return otherKey.nwkAddr == nwkAddr && otherKey.endpointId == endpointId && otherKey.clusterId == clusterId && otherKey.attributeId == attributeId;
  }

  void parseAttributeResponse(ReadAttributeResponseMessage *readAttributeResponseMessage) {

  }

  void USBDevice::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                              const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
      BindRequest bindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);

      sendData(bindRequest);
  }

  void USBDevice::sendReqBind(NwkAddr outClusterAddr, EndpointID outClusterEP, ClusterID clusterID, NwkAddr inClusterAddr, EndpointID inClusterEp) {
      if (addrLookup.count(outClusterAddr) > 0 && addrLookup.count(inClusterAddr) > 0) {
          sendReqBind(outClusterAddr, addrLookup[outClusterAddr], outClusterEP, clusterID, addrLookup[inClusterAddr], inClusterEp);
      }
  }

} /* namespace zigbee */

