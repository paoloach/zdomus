//
// Created by paolo on 01/02/18.
//

#pragma GCC diagnostic ignored "-Wpedantic"
#include <libusb.h>
#pragma GCC diagnostic pop

#include "UsbDriverFactory.h"
#include "USBDevice.h"
#include "../Configuration/Configuration.h"

namespace zigbee {
    std::unique_ptr<ZigbeeDevice>  UsbDriverFactory::getDevice(SingletonObjects * singletonObjects) {

        if (libusb_init(&usbContext) == 0) {
            //libusb_set_debug(usbContext, 4);
            BOOST_LOG_TRIVIAL(error) << "Lib usb initialized";

            return std::make_unique<DomusEngineUSBDevice>(singletonObjects, usbContext, USB_CLASS, VENDOR_ID, PRODUCT_ID, singletonObjects->getConfiguration()->getRestTimeout());
        }
        BOOST_LOG_TRIVIAL(error) << "Unable to initialize the libusb";
        throw new  std::exception();

    }
}