//
// Created by paolo on 19/10/17.
//

#ifndef DOMUS_ENGINE_USBDRIVERFACTORY_H
#define DOMUS_ENGINE_USBDRIVERFACTORY_H

#pragma GCC diagnostic ignored "-Wpedantic"
#include <libusb.h>
#pragma GCC diagnostic pop

#include "../Utils/DriverFactory.h"
#include "USBDevice.h"
#include <memory>

namespace zigbee {
    class UsbDriverFactory : public DriverFactory {
        libusb_context *usbContext;
        std::string  getName() override {return "usb";}
        std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjects * singletonObjects) override {

            if (libusb_init(&usbContext) == 0) {
                //libusb_set_debug(usbContext, 4);
                BOOST_LOG_TRIVIAL(error) << "Lib usb initialized";

                return std::make_unique<DomusEngineUSBDevice>(singletonObjects, usbContext, USB_CLASS, VENDOR_ID, PRODUCT_ID, singletonObjects->getConfiguration()->getRestTimeout());
            }
            BOOST_LOG_TRIVIAL(error) << "Unable to initialize the libusb";
            throw new  std::exception();

        }
    };
}

#endif //DOMUS_ENGINE_USBDRIVERFACTORY_H
