/*
 * USBDevice.cpp
 *
 *  Created on: 07/lug/2014
 *      Author: paolo
 */

#include <iostream>
#include <sstream>
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
#include <zigbee/messageStructure/ReadAttributeResponseErrorMsg.h>
#include <zcl/ZclAttributeUtils.h>


namespace zigbee {
    static const boost::posix_time::time_duration CHECK_NEW_MESSAGE = boost::posix_time::milliseconds(10);
    static const uint8_t raw_1234_4_0_0[] = {0x00, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_1[] = {0x01, 0x00, 0x00, 0x20, 0x10};
    static const uint8_t raw_1234_4_0_2[] = {0x02, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_3[] = {0x03, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_4[] = {0x04, 0x00, 0x00, 0x42, 0x08, 'a', 'c', 'h', 'd', 'j', 'i', 'a', 'n'};
    // model identifier
    static const uint8_t raw_1234_4_0_5[] = {0x05, 0x00, 0x00, 0x42, 0x07, 's', 'w', 'i', 't', 'c', 'h', '1'};
    static const uint8_t raw_1234_6_0_5[] = {0x05, 0x00, 0x00, 0x42, 12, 'l', 'i', 'g', 'h', 't', ' ', 's', 'w', 'i',
                                             't', 'c', 'h'};
    static const uint8_t raw_1235_7_0_5[] = {0x05, 0x00, 0x00, 0x42, 13, 'o', 'n', '/', 'o', 'f', 'f', ' ', 'o', 'u',
                                             't', 'p', 'u', 't'};
    static const uint8_t raw_1235_11_0_5[] = {0x05, 0x00, 0x00, 0x42, 12, 'o', 'n', '/', 'o', 'f', 'f', ' ', 'l', 'i',
                                              'g', 't', 'h'};


    static const uint8_t raw_1234_4_0_6[] = {0x06, 0x00, 0x00, 0x42, 8, '2', '0', '1', '6', '0', '4', '1', '2'};
    static const uint8_t raw_1234_4_0_7[] = {0x07, 0x00, 0x00, 0x30, 4};

    static const uint8_t raw_1234_4_0_16[] = {0x10, 0x00, 0x00, 0x42, 0};
    static const uint8_t raw_1234_4_0_17[] = {0x11, 0x00, 0x00, 0x30, 0};
    static const uint8_t raw_1234_4_0_18[] = {0x12, 0x00, 0x00, 0x10, 1};
    static const uint8_t raw_1234_4_0_19[] = {0x13, 0x00, 0x00, 0x30, 0};
    static const uint8_t raw_1234_4_0_20[] = {0x14, 0x00, 0x00, 0x30, 1};

    static const uint8_t raw_1235_7_6_0[] = {0x0, 0x00, 0x00, 0x10, 1};
    static const uint8_t raw_1235_11_6_0[] = {0x0, 0x00, 0x00, 0x10, 0};

    static const uint8_t raw_1235_5_1026_0[] = {0x0, 0x00, 0x00, 0x29, 0x34, 8};
    static const uint8_t raw_1232_7_1026_0[] = {0x0, 0x00, 0x00, 0x29, 0x89, 8};



    DomusEngineUSBDevice::DomusEngineUSBDevice(boost::asio::io_service &serviceIo_,
                                               std::shared_ptr<ZDevices> &zDevices_,
                                               AttributeDataContainer &attributeDataContainer_,
                                               SingletonObjects &singletonObjects, libusb_context *usbContext_,
                                               int deviceClass_, int vendor_, int product_, bool demo) : ioService(
            serviceIo_), timer{serviceIo_, CHECK_NEW_MESSAGE}, usbContext{usbContext_}, deviceClass{deviceClass_},
                                                                                                         vendorID{
                                                                                                                 vendor_},
                                                                                                         productID{
                                                                                                                 product_},
                                                                                                         handle{nullptr},
                                                                                                         demo{demo},
                                                                                                         usbResponseExecuters{
                                                                                                                 singletonObjects,
                                                                                                                 *this},
                                                                                                         zDevices(
                                                                                                                 zDevices_),
                                                                                                         attributeDataContainer(
                                                                                                                 attributeDataContainer_),
                                                                                                         singletonObjects(
                                                                                                                 singletonObjects) {
        device = nullptr;
        timer.async_wait(boost::bind(&DomusEngineUSBDevice::timerHandler, this, boost::asio::placeholders::error));

        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        0)] = raw_1234_4_0_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        1)] = raw_1234_4_0_1;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        2)] = raw_1234_4_0_2;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        3)] = raw_1234_4_0_3;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        4)] = raw_1234_4_0_4;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        5)] = raw_1234_6_0_5;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        6)] = raw_1234_4_0_6;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        7)] = raw_1234_4_0_7;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        16)] = raw_1234_4_0_16;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        17)] = raw_1234_4_0_17;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        18)] = raw_1234_4_0_18;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        19)] = raw_1234_4_0_19;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0),
                                                        20)] = raw_1234_4_0_20;

        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        0)] = raw_1234_4_0_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        1)] = raw_1234_4_0_1;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        2)] = raw_1234_4_0_2;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        3)] = raw_1234_4_0_3;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        4)] = raw_1234_4_0_4;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        5)] = raw_1234_4_0_5;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        6)] = raw_1234_4_0_6;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        7)] = raw_1234_4_0_7;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        16)] = raw_1234_4_0_16;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        17)] = raw_1234_4_0_17;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        18)] = raw_1234_4_0_18;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        19)] = raw_1234_4_0_19;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0),
                                                        20)] = raw_1234_4_0_20;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        0)] = raw_1234_4_0_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        1)] = raw_1234_4_0_1;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        2)] = raw_1234_4_0_2;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        3)] = raw_1234_4_0_3;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        4)] = raw_1234_4_0_4;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        5)] = raw_1235_7_0_5;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        6)] = raw_1234_4_0_6;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        7)] = raw_1234_4_0_7;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        16)] = raw_1234_4_0_16;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        17)] = raw_1234_4_0_17;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        18)] = raw_1234_4_0_18;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        19)] = raw_1234_4_0_19;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0),
                                                        20)] = raw_1234_4_0_20;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(7), ClusterID(6),
                                                        0)] = raw_1235_7_6_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        0)] = raw_1234_4_0_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        1)] = raw_1234_4_0_1;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        2)] = raw_1234_4_0_2;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        3)] = raw_1234_4_0_3;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        4)] = raw_1234_4_0_4;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        5)] = raw_1235_11_0_5;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        6)] = raw_1234_4_0_6;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        7)] = raw_1234_4_0_7;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        16)] = raw_1234_4_0_16;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        17)] = raw_1234_4_0_17;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        18)] = raw_1234_4_0_18;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        19)] = raw_1234_4_0_19;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0),
                                                        20)] = raw_1234_4_0_20;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(11), ClusterID(6),
                                                        0)] = raw_1235_11_6_0;

        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1235), EndpointID(5), ClusterID(1026),
                                                        0)] = raw_1235_5_1026_0;
        attributeRawData[RequestedAttributes::Attribute(NwkAddr(1232), EndpointID(7), ClusterID(1026),
                                                        0)] = raw_1232_7_1026_0;
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
        if (device != nullptr || demo) {
            return true;
        } else {
            libusb_device **devices{};

            handle = NULL;
            ssize_t devicesNum = libusb_get_device_list((libusb_context *) usbContext, &devices);

            for (int index = 0; index < devicesNum; index++) {
                libusb_device_descriptor deviceDescriptor;
                libusb_get_device_descriptor(devices[index], &deviceDescriptor);
                if (deviceDescriptor.bDeviceClass == deviceClass && deviceDescriptor.idVendor == vendorID &&
                    deviceDescriptor.idProduct == productID) {
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
                BOOST_LOG_TRIVIAL(info) << "device found";
                int result = libusb_claim_interface((libusb_device_handle *) handle, 0);
                if (result != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Unable to claim interface 0: " << strUsbError(result);
                }
            } else {
                BOOST_LOG_TRIVIAL(error) << "device not found";
            }
        }
        return device != nullptr;
    }

/**
 * Check if there is a message from the usb device and emit the right sihnal
 */
    void DomusEngineUSBDevice::getUsbMessage() {
        unsigned char data[64]{};
        int transfered{};
        if (demo && !requestedAttributes.empty()) {
            addSyntetichData();
        }
        if (device) {
            int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_IN, data, sizeof(data), &transfered, 100);
            if (result == 0) {
                BOOST_LOG_TRIVIAL(info) << "new data arrived from endpoint " << (int) BULK_ENDPOINT_IN << ",  size "
                                        << transfered;
                usbResponseExecuters.execute(data, transfered);
            } else if (result == LIBUSB_ERROR_TIMEOUT) {
                // no data
            } else {
                BOOST_LOG_TRIVIAL(error) << "from endpoint " << std::hex << (int) BULK_ENDPOINT_IN << " Transfered: "
                                         << transfered;
                BOOST_LOG_TRIVIAL(error) << strUsbError(result);
                if (libusb_reset_device(handle) != 0) {
                    handle = nullptr;
                    device = nullptr;
                }
            }
            result = libusb_bulk_transfer(handle, LOG_ENDPOINT_IN, data, sizeof(data), &transfered, 100);
            if (result == 0) {
                BOOST_LOG_TRIVIAL(trace) << "new data arrived from endpoint " << std::hex << (int) LOG_ENDPOINT_IN
                                         << ",  size " << transfered;
                usbResponseExecuters.execute(data, transfered);
            } else if (result == LIBUSB_ERROR_TIMEOUT) {
                // no data
            } else {
                BOOST_LOG_TRIVIAL(error) << "from endpoint" << (int) BULK_ENDPOINT_IN << " Transfered: " << transfered;
                BOOST_LOG_TRIVIAL(error) << strUsbError(result);
                if (libusb_reset_device(handle) != 0) {
                    handle = nullptr;
                    device = nullptr;
                }
            }
        }
    }

    void DomusEngineUSBDevice::requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                                ZigbeeAttributeId attributeId) {
        BOOST_LOG_TRIVIAL(debug) << "USBDevice request device (" << nwkAddrs << ", " << endpoint << ", " << cluster
                                 << ", " << attributeId << ")";
        if (handle != nullptr) {
            std::stringstream stream;
            AttributeValue attributeValue{nwkAddrs, endpoint, cluster, attributeId};
            int transfered{};

            BOOST_LOG_TRIVIAL(trace) << "request attribute: " << attributeValue;
            sendData(attributeValue);
        }
    }

    void DomusEngineUSBDevice::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                              ZigbeeAttributeId attrId, ZCLTypeDataType dataType, uint8_t dataValueLen,
                                              uint8_t *dataValue) {
        BOOST_LOG_TRIVIAL(debug) << "USBDevice write attribute to cluster " << std::endl;
        if (handle != nullptr) {
            WriteAttributeValueMsg writeAttributeValue{};

            writeAttributeValue.nwkAddr = nwkAddrs.getId();
            writeAttributeValue.endpoint = endpoint.getId();
            writeAttributeValue.cluster = cluster.getId();
            writeAttributeValue.attributeId = attrId;
            writeAttributeValue.dataType = static_cast<ZigbeeAttributeDataType>(dataType);
            writeAttributeValue.dataValueLen = dataValueLen;
            memcpy(writeAttributeValue.dataValue, dataValue, dataValueLen);
            sendData(writeAttributeValue);
        }
    }

    void
    DomusEngineUSBDevice::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId comandId,
                                  std::vector<uint8_t> data) {
        BOOST_LOG_TRIVIAL(debug) << "USBDevice send cmd to cluster (" << nwkAddrs << ", " << endpoint << ", " << cluster
                                 << ", " << comandId << ")";
        if (handle != nullptr) {
            ComandSend comandSend{nwkAddrs, endpoint, cluster, comandId, data};

            int transfered{};
            uint8_t *data = reinterpret_cast<uint8_t *>(&comandSend);
            std::stringstream sstream;
            for (size_t i = 0; i < sizeof(ComandSend); i++) {
                sstream << (int) data[i] << " ";
            }
            BOOST_LOG_TRIVIAL(trace) << sstream.str();
            sendData(comandSend);
        }
    }

/**
 * send request devices
 */
    bool DomusEngineUSBDevice::requestDevices() {
        int transfered;
        if (handle == nullptr) {
            return false;
        }
        GenericMessage genericMessage;

        genericMessage.msgCode = REQ_ALL_NODES;
        BOOST_LOG_TRIVIAL(info) << "Request all nodes";
        sendData(genericMessage);
        return true;
    }

    bool DomusEngineUSBDevice::enableLog() {
        int transfered;
        if (handle == nullptr) {
            return false;
        }
        GenericMessage genericMessage;

        genericMessage.msgCode = 0x21;
        BOOST_LOG_TRIVIAL(info) << "Enable usb logs";
        sendData(genericMessage);
        return true;
    }

    void DomusEngineUSBDevice::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(info) << "Request active endpons for " << nwkAddr;
        ReqActiveEndpointsMessage request{};
        request.nwkAddr = nwkAddr.getId();

        int transfered{};

        int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request),
                                          &transfered, 1000);
        sendData(request);
    }


    void DomusEngineUSBDevice::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN],
                                           EndpointID outClusterEP, ClusterID clusterID,
                                           const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "Request to bind ";
        BindRequest bindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);
        sendData(bindRequest);
    }

    void DomusEngineUSBDevice::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN],
                                             EndpointID outClusterEP, ClusterID clusterID,
                                             const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "Request to unbind ";
        UnbindRequest unbindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);
        sendData(unbindRequest);
    }


    void DomusEngineUSBDevice::requestBindTable(NwkAddr nwkAddrs) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(info) << "Send request for bind table at " << nwkAddrs;
        ReqBindTable request(nwkAddrs.getId());
        sendData(request);
    }

    void DomusEngineUSBDevice::requestAttributes(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster,
                                                 ZigbeeAttributeIds &attributeIds) {
        requestedAttributes = RequestedAttributes(nwkAddrs, endpoint, cluster, attributeIds);
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "USBDevice request device (" << nwkAddrs << ", " << endpoint << ", " << cluster
                                 << ", " << "attribute: " << attributeIds << ")";


        std::stringstream stream;
        AttributeValue attributeValue{nwkAddrs, endpoint, cluster, attributeIds};
        int transfered{};

        BOOST_LOG_TRIVIAL(trace) << "request attribute: " << attributeValue;

        sendData(attributeValue, sizeof(GenericMessage) + sizeof(ZigbeeNwkAddress) + sizeof(ZigbeeEndpoint) + sizeof(ZigbeeClusterId) + sizeof(uint8_t) + sizeof(ZigbeeAttributeId) * attributeValue.numAttr);
    }

    void DomusEngineUSBDevice::requestReset() {
        if (handle == nullptr) {
            return;
        }
        GenericMessage resetMessage{REQ_RESET};
        int transfered{};

        int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &resetMessage,
                                          sizeof(GenericMessage), &transfered, 1000);
        sendData(resetMessage);
    }

    void DomusEngineUSBDevice::addSyntetichData() {
        RequestedAttributes::Attribute &firstAttr = requestedAttributes.attributes[0];
        NwkAddr nwkAddr = firstAttr.nwkAddrs;
        EndpointID endpoint = firstAttr.endpoint;
        ClusterID cluster = firstAttr.clusterID;

        std::vector<RequestedAttributes::Attribute> attributesToSend{getAttributeToSend(nwkAddr, endpoint, cluster)};
        size_t size = calcTotalSize(attributesToSend) + sizeof(ReadAttributeResponseMessage);

        uint8_t *data = new uint8_t[size];
        ReadAttributeResponseMessage *message = reinterpret_cast<ReadAttributeResponseMessage *>(data);
        message->networkAddr = nwkAddr.getId();
        message->endpoint = endpoint.getId();
        message->clusterId = cluster.getId();
        message->generticDataMsg = ATTRIBUTE_VALUES;
        message->numAttributes = attributesToSend.size();
        message->panId = 0;
        message->type = 0;
        uint8_t *rawData = data + sizeof(ReadAttributeResponseMessage);
        BOOST_LOG_TRIVIAL(info) << "start attributes data: " << (void *) rawData;
        uint8_t *endData = fillRawData(attributesToSend, rawData);
        usbResponseExecuters.execute(data, size);
        delete[]data;
    }

    std::vector<RequestedAttributes::Attribute>
    DomusEngineUSBDevice::getAttributeToSend(NwkAddr nwkAddr, EndpointID endpoint, ClusterID cluster) {
        std::vector<RequestedAttributes::Attribute> attributesToSend;
        std::vector<RequestedAttributes::Attribute> attributesRemained;

        for (auto &attribute: requestedAttributes.attributes) {
            if (attribute.nwkAddrs == nwkAddr && attribute.endpoint == endpoint && attribute.clusterID == cluster) {
                attributesToSend.push_back(attribute);
            } else {
                attributesRemained.push_back(attribute);
            }
        }
        requestedAttributes.attributes = attributesRemained;
        return attributesToSend;
    }

    size_t DomusEngineUSBDevice::calcTotalSize(std::vector<RequestedAttributes::Attribute> &attributes) {
        size_t totaleSize = 0;
        for (auto &attribute: attributes) {
            const uint8_t *raw = attributeRawData[attribute];
            const AttributeResponse *response = reinterpret_cast<const AttributeResponse *>(raw);
            const uint8_t *rawData = raw + sizeof(AttributeResponse);
            size_t size =
                    ZclAttributeUtils::zclGetAttrDataLength(response->dataType, rawData) + sizeof(AttributeResponse);
            BOOST_LOG_TRIVIAL(info) << "id: " << attribute.attributeId << ", dataType: " << (int) response->dataType
                                    << ",  size: " << size;
            totaleSize += size;
        }
        return totaleSize;
    }

    uint8_t *DomusEngineUSBDevice::fillRawData(std::vector<RequestedAttributes::Attribute> &attributes, uint8_t *data) {
        for (auto &attribute: attributes) {
            const uint8_t *raw = attributeRawData[attribute];
            const AttributeResponse *response = reinterpret_cast<const AttributeResponse *>(raw);
            const uint8_t *rawData = raw + sizeof(AttributeResponse);
            size_t size =
                    ZclAttributeUtils::zclGetAttrDataLength(response->dataType, rawData) + sizeof(AttributeResponse);
            BOOST_LOG_TRIVIAL(info) << "id: " << attribute.attributeId << ", dataType: " << (int) response->dataType
                                    << ",copy size: " << size;
            memcpy(data, raw, size);
            data += size;
        }
        return data;
    }


} /* namespace zigbee */
