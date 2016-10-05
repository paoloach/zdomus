/*
 * SingletonObjects.cpp
 *
 *  Created on: 19/giu/2015
 *      Author: Paolo Achdjian
 */

#include <libusb.h>
#include <boost/log/trivial.hpp>


#include "SingletonObjects.h"
#include "../usb/usbConfig.h"
#include "../usb/USBDevice.h"
#include "../Configuration/Configuration.h"
#include "../httpServer/FixedPathContainer.h"
#include "../JavaScript/JSManager.h"
#include "DeviceInfoDispatcher.h"


namespace zigbee {

    static constexpr int MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY{100};

    SingletonObjects::SingletonObjects(std::string &&configurationFileName, bool demo) :
            attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY} ,attributeWriter{*this}, topology{*this}{

        if (demo){
            BOOST_LOG_TRIVIAL(info) << "----------- DEMO MODE ----------";
        }

        zDevices = std::make_unique<ZDevices>();
        if (libusb_init(&usbContext) != 0) {
            BOOST_LOG_TRIVIAL(error) << "Unable to initialize the libusb";
        } else {
            //libusb_set_debug(usbContext, 4);
            BOOST_LOG_TRIVIAL(error) << "Lib usb initialized";

            zigbeeDevice = std::make_unique<DomusEngineUSBDevice>(io, *this,
                                                                  usbContext,
                                                                  USB_CLASS, VENDOR_ID, PRODUCT_ID, demo);
            if (zigbeeDevice->isPresent()) {
                zigbeeDevice->enableLog();
                NwkAddr addr;
               zigbeeDevice->requestBindTable(addr);
                sleep(1);
            }
        }

        std::ifstream streamConfig(configurationFileName);
        if (streamConfig.fail()) {
            BOOST_LOG_TRIVIAL(error) << "Unable to open configuration file " << configurationFileName;
            exit(-1);
        }
        configuration = std::make_shared<Configuration>(streamConfig);
        fixedPathContainer = std::make_shared<http::FixedPathContainer>();

        jsManager = std::make_shared<JSManager>(*this);
    }

    SingletonObjects::SingletonObjects() :
            attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY}, attributeWriter{*this}, topology{*this} {

    }
} /* namespace zigbee */

