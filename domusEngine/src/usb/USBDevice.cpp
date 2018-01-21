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
#include "messages/PowerNodeRequestMessage.h"
#include <zigbee/messageStructure/ReqBindTable.h>
#include <zigbee/messageStructure/AttributeValue.h>
#include <zigbee/messageStructure/ComandSend.h>
#include <zigbee/messageStructure/WriteAttributeValue.h>
#include <zigbee/messageStructure/BindRequest.h>
#include <zigbee/messageStructure/UnbindRequest.h>
#include <zigbee/messageStructure/ReadAttributeResponseErrorMsg.h>
#include <zigbee/messageStructure/ReqDeviceInformation.h>
#include <zigbee/messageStructure/IEEEAddressRequestMessage.h>
#include <boost/fiber/algo/round_robin.hpp>

namespace zigbee {
    static const boost::posix_time::time_duration CHECK_NEW_MESSAGE = boost::posix_time::milliseconds(10);


    DomusEngineUSBDevice::DomusEngineUSBDevice(SingletonObjects * singletonObjects, libusb_context *usbContext_, int deviceClass_, int vendor_, int product_,
                                               std::chrono::seconds timeout) : ZigbeeDevice(timeout), stop(false), usbContext{usbContext_}, deviceClass{deviceClass_},
                                                                               vendorID{vendor_}, productID{product_}, handle{nullptr},
                                                                               usbResponseExecuters{singletonObjects, *this} {
        device = nullptr;
        getMessageTh = std::thread([this] { this->timerHandler(); });
    }


    void DomusEngineUSBDevice::timerHandler() {
        boost::fibers::use_scheduling_algorithm<boost::fibers::algo::round_robin>();
        powerNodeQueue.startDequeFiber();

        while (!stop) {

            if (isPresent()) {
                getUsbMessage();
            }
            usleep(1000);
        }
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

            handle = nullptr;
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
            if (handle != nullptr) {
                BOOST_LOG_TRIVIAL(info) << "device found";
                int result = libusb_claim_interface((libusb_device_handle *) handle, 0);
                if (result != 0) {
                    BOOST_LOG_TRIVIAL(error) << "Unable to claim interface 0: " << strUsbError(result);
                }
            } else {
                //BOOST_LOG_TRIVIAL(error) << "device not found";
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
        if (device) {
            int result = libusb_bulk_transfer(handle, BULK_ENDPOINT_IN, data, sizeof(data), &transfered, 100);
            if (result == 0) {
                BOOST_LOG_TRIVIAL(info) << "new data arrived from endpoint " << (int) BULK_ENDPOINT_IN << ",  size " << transfered;
                usbResponseExecuters.execute(data, transfered);
            } else if (result == LIBUSB_ERROR_TIMEOUT) {
                // no data
            } else {
                BOOST_LOG_TRIVIAL(error) << "from endpoint " << std::hex << (int) BULK_ENDPOINT_IN << " Transfered: " << transfered;
                BOOST_LOG_TRIVIAL(error) << strUsbError(result);
                if (libusb_reset_device(handle) != 0) {
                    handle = nullptr;
                    device = nullptr;
                }
            }
            result = libusb_bulk_transfer(handle, LOG_ENDPOINT_IN, data, sizeof(data), &transfered, 100);
            if (result == 0) {
                BOOST_LOG_TRIVIAL(trace) << "new data arrived from endpoint " << std::hex << (int) LOG_ENDPOINT_IN << ",  size " << transfered;
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

    void DomusEngineUSBDevice::requestAttribute(const AttributeKey &key) {
        BOOST_LOG_TRIVIAL(info) << "USBDevice request device " << key;
        if (handle != nullptr) {
            std::stringstream stream;
            AttributeValue attributeValue{key};

            BOOST_LOG_TRIVIAL(trace) << "request attribute: " << attributeValue;

            auto serializeData = attributeValue.serialize();
            std::unique_ptr<uint8_t> data(new uint8_t[serializeData.size()]);
            std::copy(serializeData.begin(), serializeData.end(), data.get());

            int transfered;

            int result = libusb_bulk_transfer((libusb_device_handle *) handle, BULK_ENDPOINT_OUT, data.get(), serializeData.size(), &transfered, 1000);
            if (result == 0) {
                BOOST_LOG_TRIVIAL(trace) << "request sent";
            } else {
                BOOST_LOG_TRIVIAL(error) << "Error send data: " << strUsbError(result) << ", transfered: " << transfered << " insteado of " << serializeData.size();
            }
        }
    }

    void
    DomusEngineUSBDevice::writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attrId, ZCLTypeDataType dataType, uint8_t dataValueLen,
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

    void DomusEngineUSBDevice::sendCmd(NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId comandId, std::vector<uint8_t> data) {

        BOOST_LOG_TRIVIAL(debug) << "USBDevice send cmd to cluster (" << nwkAddrs << ", " << endpoint << ", " << cluster << ", " << comandId << ")";
        if (handle != nullptr) {
            ComandSend comandSend{nwkAddrs, endpoint, cluster, comandId, data};

            uint8_t *data = reinterpret_cast<uint8_t *>(&comandSend);
            std::stringstream sstream;
            for (size_t i = 0; i < sizeof(ComandSend); i++) {
                sstream << (int) data[i] << " ";
            }
            BOOST_LOG_TRIVIAL(trace) << sstream.str();
            sendData(comandSend);
        }
    }

    bool DomusEngineUSBDevice::enableLog() {
        if (handle == nullptr) {
            return false;
        }
        GenericMessage genericMessage;

        genericMessage.msgCode = 0x21;
        BOOST_LOG_TRIVIAL(info) << "Enable usb logs";
        sendData(genericMessage);
        return true;
    }

    void DomusEngineUSBDevice::requestNodePower(NwkAddr nwkAddr) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(info) << "Request active endpons for " << nwkAddr;
        PowerNodeRequestMessage request{nwkAddr};

        int transferd;

        libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request), &transferd, 1000);
        sendData(request);
    }

    void DomusEngineUSBDevice::requestActiveEndpoints(NwkAddr nwkAddr) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(info) << "Request active endpons for " << nwkAddr;
        ReqActiveEndpointsMessage request{};
        request.nwkAddr = nwkAddr.getId();

        int transfered{};

        libusb_bulk_transfer(handle, BULK_ENDPOINT_OUT, (unsigned char *) &request, sizeof(request), &transfered, 1000);
        sendData(request);
    }


    void DomusEngineUSBDevice::sendReqBind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
                                           const uint8_t inClusterAddr[Z_EXTADDR_LEN], EndpointID inClusterEp) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "Request to bind ";
        BindRequest bindRequest(destAddr, outClusterAddr, outClusterEP, clusterID, inClusterAddr, inClusterEp);
        sendData(bindRequest);
    }

    void DomusEngineUSBDevice::sendReqUnbind(NwkAddr destAddr, const uint8_t outClusterAddr[Z_EXTADDR_LEN], EndpointID outClusterEP, ClusterID clusterID,
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

    void DomusEngineUSBDevice::requestAttributes(AttributesKey &key) {
        if (handle == nullptr) {
            return;
        }
        BOOST_LOG_TRIVIAL(debug) << "USBDevice request device " << key;

        std::stringstream stream;
        AttributeValue attributeValue{key.networkAddress, key.endpoint, key.clusterId, key.attributesId};
        BOOST_LOG_TRIVIAL(trace) << "request attribute: " << attributeValue;

        sendData(attributeValue, sizeof(GenericMessage) + sizeof(ZigbeeNwkAddress) + sizeof(ZigbeeEndpoint) + sizeof(ZigbeeClusterId) + sizeof(uint8_t) +
                                 sizeof(ZigbeeAttributeId) * attributeValue.numAttr);
    }

    void DomusEngineUSBDevice::requestReset() {
        if (handle == nullptr) {
            return;
        }
        GenericMessage resetMessage{REQ_RESET};
        sendData(resetMessage);
    }


    void DomusEngineUSBDevice::sendReqDeviceInfo(NwkAddr networkId) {
        if (handle == nullptr) {
            return;
        }
        ReqDeviceInformation message{networkId.getId()};
        sendData(message);
    }

    void DomusEngineUSBDevice::getIEEEAddress(NwkAddr nwkAddr, ZDPRequestType requestType, uint8_t startIndex) {
        if (handle == nullptr) {
            return;
        }
        IEEEAddressRequestMessage message(nwkAddr.getId(), requestType, startIndex);
        sendData(message);
    }

    void DomusEngineUSBDevice::removeDevice(NwkAddr networkId) {
        BOOST_LOG_TRIVIAL(info) << "TO BE IMPLEMENTED";

    }


} /* namespace zigbee */
