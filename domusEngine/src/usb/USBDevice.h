/*
 * USBDevice.h
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#ifndef USBDEVICE_H_
#define USBDEVICE_H_

#include <boost/log/trivial.hpp>
#include <boost/signals2.hpp>
#include <map>
#include <boost/asio.hpp>
#include <zigbee/ZigbeeDevice.h>
#include <zcl/ZCLDataType.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <libusb.h>
#pragma GCC diagnostic pop
#include "usbConfig.h"
#include "../ZigbeeData/ZDevices.h"
#include "BindResponse.h"
#include "UsbResponseExecutors.h"
#include "RequestedAttributes.h"


namespace zigbee {

    class SingletonObjects;

    static const int STANDARD_REQUEST_TYPE{0};
    static const int CLASS_REQUEST_TYPE{0x20};
    static const unsigned char VENDOR_REQUEST_TYPE = 0x40;
    static const int RESERVED_REQUEST_TYPE{0x60};

    static const unsigned char REQUEST_DEVICES = 0x20;

    class DomusEngineUSBDevice : public ZigbeeDevice {
    public:
        DomusEngineUSBDevice(SingletonObjects * singletonObjects, libusb_context *usbContext, int deviceClass, int vendorID, int productID, std::chrono::seconds timeout);

        ~DomusEngineUSBDevice() override {
            stop = true;
            getMessageTh.join();
        };

    public:
        bool isPresent() override;


        bool enableLog() override;

        void getUsbMessage();

        void getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) override;

        void requestAttribute(const AttributeKey &) override;

        void requestAttributes(AttributesKey & key) override;

        void requestReset() override;

        void removeDevice(NwkAddr networkId) override ;

        void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen,
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

        void requestNodePower(NwkAddr nwkAddr) override;

        void requestActiveEndpoints(NwkAddr nwkAddr) override;

        void sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                         EndpointID inClusterEp) override;

        void sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID, const uint8_t inClusterAddr[Z_EXTADDR_LEN],
                           EndpointID inClusterEp) override;

        void sendReqDeviceInfo(NwkAddr networkId) override;

        void requestBindTable(NwkAddr nwkAddrs) override;

        void getNodeDescriptor(NwkAddr nwkAddr) override;

        void getLqiResponse(NwkAddr nwkAddr, uint index) override;

    private:
        bool stop;
        std::thread getMessageTh;
        libusb_context *usbContext;
        int deviceClass;
        int vendorID;
        int productID;
        libusb_device *device;
        libusb_device_handle *handle;
        UsbResponseExecutors usbResponseExecuters;
        std::vector<AnnunceCallback> annunceSignal;
        std::vector<SimpleDescCallback> simpleDescSignal;
        std::vector<BindTableResponseCallback> bindTableResponseSignal;

    private:
        template<typename T>
        void sendData(const T &);

        template<typename T>
        void sendData(const T &, size_t size);

        void timerHandler();

        std::string strUsbError(int);

        std::vector<RequestedAttributes::Attribute> getAttributeToSend(NwkAddr nwkAddr, EndpointID endpoint, ClusterID cluster);

    };

    template<typename T>
    inline void zigbee::DomusEngineUSBDevice::sendData(const T &data) {
        sendData(data, sizeof(data));
    }

    template<typename T>
    inline void zigbee::DomusEngineUSBDevice::sendData(const T &data, size_t size) {
        int transfered;

        int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, (unsigned char *) &data, size, &transfered, 1000);
        if (result == 0) {
            BOOST_LOG_TRIVIAL(trace) << "request sent";
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error send data: " << strUsbError(result) << ", transfered: " << transfered << " insteado of " << sizeof(T);
        }
    }

} /* namespace zigbee */

#endif /* USBDEVICE_H_ */
