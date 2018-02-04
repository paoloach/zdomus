//
// Created by paolo on 19/10/17.
//

#ifndef DOMUS_ENGINE_USBDRIVERFACTORY_H
#define DOMUS_ENGINE_USBDRIVERFACTORY_H

#include "../Utils/DriverFactory.h"
#include <memory>

struct libusb_context;
namespace zigbee {
    class UsbDriverFactory : public DriverFactory {
        libusb_context *usbContext;
        std::string  getName() override {return "usb";}
        std::unique_ptr<ZigbeeDevice>  getDevice(SingletonObjects * singletonObjects) override;
    };
}

#endif //DOMUS_ENGINE_USBDRIVERFACTORY_H
