/*
 * USBDevice.cpp
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#include <iostream>
#include <iomanip>
#include <libusb-1.0/libusb.h>
#include <boost/log/trivial.hpp>

#include "usbConfig.h"
#include "USBDevice.h"
#include <zigbee/messageStructure/ReqBindTable.h>
#include <zigbee/messageStructure/AttributeValue.h>
#include <zigbee/messageStructure/ComandSend.h>
#include <zigbee/messageStructure/WriteAttributeValue.h>
#include <zigbee/messageStructure/BindRequest.h>
#include <zigbee/messageStructure/UnbindRequest.h>
#include "../Utils/SingletonObjects.h"

namespace zigbee {

  static const boost::posix_time::time_duration CHECK_NEW_MESSAGE = boost::posix_time::seconds(1);

  DomusEngineUSBDevice::DomusEngineUSBDevice(boost::asio::io_service &serviceIo_, std::shared_ptr<ZDevices> &zDevices_, AttributeDataContainer &attributeDataContainer_,
                                             SingletonObjects & singletonObjects,
                                             libusb_context *usbContext_, int deviceClass_, int vendor_, int product_) :
          ioService(serviceIo_), timer(serviceIo_, CHECK_NEW_MESSAGE), usbContext(usbContext_), deviceClass{deviceClass_}, vendorID{vendor_}, productID{product_},
          handle(
                  nullptr), zDevices(zDevices_), attributeDataContainer(attributeDataContainer_),singletonObjects(singletonObjects) {
      device = nullptr;
      timer.async_wait(boost::bind(&DomusEngineUSBDevice::timerHandler, this, boost::asio::placeholders::error));
  }


  void DomusEngineUSBDevice::timerHandler(const boost::system::error_code &) {
      if (isPresent()) {
          getUsbMessage();
      }
      timer.expires_from_now(CHECK_NEW_MESSAGE);
      timer.async_wait(boost::bind(&DomusEngineUSBDevice::timerHandler, this, boost::asio::placeholders::error));
  }

  void emptySlot(void) {

  }

  std::string DomusEngineUSBDevice::strUsbError(int error) {
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
  bool DomusEngineUSBDevice::isPresent() {
      if (device != nullptr) {
          return true;
      } else {
          libusb_device **devices{};

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
      }
      return device != nullptr;
  }

/**
 * Check if there is a message from the usb device and emit the right sihnal
 */
  void DomusEngineUSBDevice::getUsbMessage() {
      unsigned char data[1024]{};
      int transfered{};
      if (device) {
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_IN, data, sizeof(data), &transfered, 10);
          if (result == 0) {
              BOOST_LOG_TRIVIAL(info) << "new data arrived: size " << transfered;
              parseUsbMessage(data, transfered);
          } else if (result == LIBUSB_ERROR_TIMEOUT) {
              // no data
          } else {
              BOOST_LOG_TRIVIAL(error) << " Transfered: " << transfered;
              BOOST_LOG_TRIVIAL(error) << strUsbError(result) ;
              if (libusb_reset_device(handle) != 0){
                  handle= nullptr;
              }
          }
      }
  }

  void DomusEngineUSBDevice::parseUsbMessage(unsigned char *data, int length) {
      AnnunceMessage *annunceMessage{};
      SimpleDescMessage *simpleDescMessage{};
      ReadAttributeResponseMessage *readAttributeResponseMessage{};
      if (length > 0) {
          switch (*data) {
              case ANNUNCE_MSG:
                  annunceMessage = (AnnunceMessage *) data;
                  zDevices->put(*annunceMessage);
                  BOOST_LOG_TRIVIAL(info) << "Annunce signal" ;
                  requestActiveEndpoints(NwkAddr(annunceMessage->nwkAddr));
                  requestBindTable(NwkAddr(annunceMessage->nwkAddr));
                  break;
              case SIMPLE_DESC:
                  simpleDescMessage = (SimpleDescMessage *) data;
                  zDevices->put(*simpleDescMessage);
                  BOOST_LOG_TRIVIAL(info) << "Simple desciption message ";
                  break;
              case ATTRIBUTE_VALUES:
                  BOOST_LOG_TRIVIAL(info) << "Read response attribute value";
                  readAttributeResponseMessage = (ReadAttributeResponseMessage *) data;
                  attributeDataContainer.push(*readAttributeResponseMessage);
                  break;
              case BIND_TABLE: {
                  std::vector<BindResponse> responses;
                  BOOST_LOG_TRIVIAL(info) << "Bind response " << std::endl;

                  int count = data[1];
                  data +=2;
                  BOOST_LOG_TRIVIAL(info) << " entry: " << count;
                  for (int i=0; i < count; i++){
                      singletonObjects.getBindTable().add(std::move(BindResponse(data)));
                  }
                  break;
              }
              default:
                  BOOST_LOG_TRIVIAL(info) << "Unknow message type:  "  << (int)(*data)<< std::endl;

          }
      }
  }

  void DomusEngineUSBDevice::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) {
      std::cout << "USBDevice request device (" << nwkAddrs << ", " << endpoint << ", " << cluster << ", " << attributeId << ")" << std::endl;
      if (handle != nullptr) {
          AttributeValue attributeValue{};
          attributeValue.nwkAddr = nwkAddrs.getId();
          attributeValue.endpoint = endpoint.getId();
          attributeValue.cluster = cluster.getId();
          attributeValue.attribute = attributeId;

          int transfered{};
          std::cout << "request attribute: ";
          for (unsigned int i = 0; i < sizeof(attributeValue); i++) {
              std::cout << (int) (*((unsigned char *) &attributeValue + i)) << " - ";
          }
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &attributeValue, sizeof(attributeValue), &transfered,
                                            10);
          if (result == 0) {
              std::cout << "request sent" << std::endl;
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void DomusEngineUSBDevice::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attrId, ZCLTypeDataType dataType,
                                            uint8_t dataValueLen,
                                            uint8_t *dataValue) {
      std::cout << "USBDevice write attribute to cluster " << std::endl;
      if (handle != nullptr) {
          WriteAttributeValueMsg writeAttributeValue{};

          writeAttributeValue.nwkAddr = nwkAddrs.getId();
          writeAttributeValue.endpoint = endpoint.getId();
          writeAttributeValue.cluster = cluster.getId();
          writeAttributeValue.attributeId = attrId;
          writeAttributeValue.dataType = static_cast<ZigbeeAttributeDataType>(dataType);
          writeAttributeValue.dataValueLen = dataValueLen;
          memcpy(writeAttributeValue.dataValue, dataValue, dataValueLen);
          int transfered{};
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

  void DomusEngineUSBDevice::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId comandId, std::vector<uint8_t> data) {
      std::cout << "USBDevice send cmd to cluster (" << nwkAddrs << ", " << endpoint << ", " << cluster << ", " << comandId << ")" << std::endl;
      if (handle != nullptr) {
          ComandSend comandSend{nwkAddrs, endpoint, cluster, comandId, data};

          int transfered{};
          int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &comandSend, sizeof(comandSend), &transfered, 10);
          if (result == 0) {
              std::cout << "request sent" << std::endl;
          } else {
              std::cerr << strUsbError(result) << std::endl;
          }
      }
  }

  void DomusEngineUSBDevice::parseAttributeResponse(ReadAttributeResponseMessage *readAttributeResponseMessage) {
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
  bool DomusEngineUSBDevice::requestDevices() {
      int transfered;
      GenericMessage genericMessage;

      genericMessage.msgCode = REQ_ALL_NODES;
      int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &genericMessage, sizeof(genericMessage), &transfered, 10);
      if (result == 0) {
          std::cout << "request sent" << std::endl;
      } else {
          std::cerr << strUsbError(result) << std::endl;
      }
      return false;
  }

  void DomusEngineUSBDevice::requestActiveEndpoints(NwkAddr nwkAddr) {
      ReqActiveEndpointsMessage request{};
      request.nwkAddr = nwkAddr.getId();

      int transfered{};

      int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request), &transfered, 10);
      if (result == 0) {
          std::cout << "request sent" << std::endl;
      } else {
          std::cerr << strUsbError(result) << std::endl;
      }
  }

  bool DomusEngineUSBDevice::AttributeKey::operator<(const AttributeKey &otherKey) const {
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

  bool DomusEngineUSBDevice::AttributeKey::operator==(const AttributeKey &otherKey) const {
      return otherKey.nwkAddr == nwkAddr && otherKey.endpointId == endpointId && otherKey.clusterId == clusterId && otherKey.attributeId == attributeId;
  }

  void parseAttributeResponse(ReadAttributeResponseMessage *) {

  }


  void DomusEngineUSBDevice::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                         const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
      BindRequest bindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);
      sendData(bindRequest);
  }

  void DomusEngineUSBDevice::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                           const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
      UnbindRequest unbindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);
      sendData(unbindRequest);
  }


  void DomusEngineUSBDevice::requestBindTable(NwkAddr nwkAddrs) {
      BOOST_LOG_TRIVIAL(info) << "Send request for bind table at " << nwkAddrs;
      ReqBindTable request(nwkAddrs.getId());
      sendData(request);
  }
} /* namespace zigbee */
