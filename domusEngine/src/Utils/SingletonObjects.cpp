/*
 * SingletonObjects.cpp
 *
 *  Created on: 19/giu/2015
 *      Author: Paolo Achdjian
 */

#include <libusb.h>
#include <zcl/ClusterTypeFactory.h>

#include "SingletonObjects.h"
#include "../usb/usbConfig.h"
#include "../usb/USBDevice.h"
#include "../Configuration/Configuration.h"
#include "../httpServer/FixedPathContainer.h"
#include "../JavaScript/JSManager.h"


namespace zigbee {

    static constexpr int MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY{100};

    SingletonObjects::SingletonObjects(std::string &&configurationFileName) :
            attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY} {
        zDevices = std::make_shared<ZDevices>();
        if (libusb_init(&usbContext) != 0) {
            std::cerr << "Unable to initialize the libusb" << std::endl;
        } else {
            std::cout << "Lib usb initialized" << std::endl;

            zigbeeDevice = std::make_shared<DomusEngineUSBDevice>(io, zDevices, attributeDataContainer, *this,usbContext,
                                                                  USB_CLASS, VENDOR_ID, PRODUCT_ID);
            if (zigbeeDevice->isPresent()) {
                zigbeeDevice->requestDevices();
                NwkAddr addr;
                zigbeeDevice->requestBindTable(addr);
            }
        }

        std::ifstream streamConfig(configurationFileName);
        if (streamConfig.fail()) {
            std::cerr << "Unable to open configuration file " << configurationFileName << std::endl;
            exit(-1);
        }
        configuration = std::make_shared<Configuration>(streamConfig);
        fixedPathContainer = std::make_shared<http::FixedPathContainer>();
        clusterTypeFactory = std::make_shared<ClusterTypeFactory>();
        jsManager = std::make_shared<JSManager>(*this);
    }

    SingletonObjects::SingletonObjects() :
            attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY} {

    }
} /* namespace zigbee */

