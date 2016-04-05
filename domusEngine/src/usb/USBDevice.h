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


  static const int STANDARD_REQUEST_TYPE{0};
  static const int CLASS_REQUEST_TYPE{0x20};
  static const unsigned char VENDOR_REQUEST_TYPE = 0x40;
  static const int RESERVED_REQUEST_TYPE{0x60};

  static const unsigned char REQUEST_DEVICES = 0x20;

  class DomusEngineUSBDevice : public ZigbeeDevice {
  private:
      struct AttributeKey {
          AttributeKey(NwkAddr nwkAddress, ZigbeeEndpoint endpoint, ZigbeeClusterId cluster, ZigbeeAttributeId attributeId) :
                  nwkAddr(nwkAddress), endpointId(endpoint), clusterId(cluster), attributeId(attributeId) {
          }

          NwkAddr nwkAddr;
          ZigbeeEndpoint endpointId;
          ZigbeeClusterId clusterId;
          ZigbeeAttributeId attributeId;

          bool operator<(const AttributeKey &otherKey) const;

          bool operator==(const AttributeKey &otherKey) const;
      };

      using AttributeValueSignalMap = std::multimap<AttributeKey, NewAttributeValueCallback>;
  public:
      DomusEngineUSBDevice(boost::asio::io_service &io, std::shared_ptr<ZDevices> &zDevices, AttributeDataContainer &attributeDataContainer, libusb_context *usbContext,
                           int deviceClass, int vendorID, int productID);

      virtual ~DomusEngineUSBDevice() = default;

  public:
      bool isPresent() override;

      bool requestDevices() override;

      void getUsbMessage() override;

      void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId) override;

      virtual void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                  uint8_t *dataValue) override;

      void sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data = std::vector<uint8_t>()) override;

      void registerForAnnunceMessage(AnnunceCallback subscriber) override {
          annunceSignal.push_back(subscriber);
      }

      void registerForSimpleDescMessage(SimpleDescCallback subscriber) override {
          simpleDescSignal.push_back(subscriber);
      }

      void registerForBindTableMessage(BindTableResponseCallback subscriber) override {
          bindTableResponseSignal.push_back(subscriber);
      }

      void registerForAttributeCmd(NwkAddr, const EndpointID, ClusterID, ZigbeeAttributeCmdId, const std::function<void()>) override {
      }

      void registerForAttributeValue(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
                                     const NewAttributeValueCallback subscriber) override {
          AttributeKey key(nwkAddrs, endpoint.getId(), cluster.getId(), attributeId);
          attributeValueSignalMap.insert(AttributeValueSignalMap::value_type(key, subscriber));
      }

      void requestActiveEndpoints(NwkAddr nwkAddr);

      virtual void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                               const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) override;

      virtual void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                               const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) override;

      void requestBindTable(NwkAddr nwkAddrs) override;

  private:
      boost::asio::io_service &ioService;
      boost::asio::deadline_timer timer;
      libusb_context *usbContext;
      int deviceClass;
      int vendorID;
      int productID;
      libusb_device *device;
      libusb_device_handle *handle;
      std::shared_ptr<ZDevices> zDevices;
      AttributeDataContainer &attributeDataContainer;
      std::vector<AnnunceCallback> annunceSignal;
      std::vector<SimpleDescCallback> simpleDescSignal;
      std::vector<BindTableResponseCallback> bindTableResponseSignal;
      AttributeValueSignalMap attributeValueSignalMap;

  private:
      template<typename T>
      void sendData(const T &);

      void timerHandler(const boost::system::error_code &error);

      void parseUsbMessage(unsigned char *data, int length);

      void parseAttributeResponse(ReadAttributeResponseMessage *readAttributeResponseMessage);

      std::string strUsbError(int);
  };

  template<typename T>
  inline void zigbee::DomusEngineUSBDevice::sendData(const T &data) {
      int transfered;

      int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &data, sizeof(data), &transfered, 10);
      if (result == 0) {
          std::cout << "request sent" << std::endl;
      } else {
          std::cerr << strUsbError(result) << std::endl;
      }
  }

} /* namespace zigbee */

#endif /* USBDEVICE_H_ */
