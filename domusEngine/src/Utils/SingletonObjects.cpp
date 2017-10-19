/*
 * SingletonObjects.cpp
 *
 *  Created on: 19/giu/2015
 *      Author: Paolo Achdjian
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <libusb.h>
#pragma GCC diagnostic pop
#include <boost/log/trivial.hpp>


#include "SingletonObjects.h"
#include "../Configuration/Configuration.h"
#include "../JavaScript/JSManager.h"
#include "../DemoDriver/DemoDevice.h"

namespace zigbee {

    static constexpr int MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY{100};

    SingletonObjects::SingletonObjects(std::string &&configurationFileName, std::string driverName, std::vector<DriverFactory *> && driverFactories) :
            attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY}, attributeWriter{*this}, topology{*this}, restHandler{*this} {
        std::ifstream streamConfig(configurationFileName);
        if (streamConfig.fail()) {
            BOOST_LOG_TRIVIAL(error) << "Unable to open configuration file " << configurationFileName;
            exit(-1);
        }
        configuration = std::make_shared<Configuration>(streamConfig);
        zDevices = std::make_unique<ZDevices>();

        for(auto driverFactory : driverFactories){
            if (driverFactory->getName() == driverName){
                zigbeeDevice = std::move(driverFactory->getDevice(this));
            }
        }

        if (!zigbeeDevice){
            BOOST_LOG_TRIVIAL(error) << "Driver available: usb, serial, demo";
        }


        if (zigbeeDevice) {
            clusters = Clusters{zigbeeDevice.get()};
            if (zigbeeDevice->isPresent()) {
                zigbeeDevice->enableLog();
                NwkAddr addr;
                // zigbeeDevice->requestBindTable(addr);
                sleep(1);
            }
        }


        jsManager = std::make_shared<JSManager>(*this);
    }

    SingletonObjects::SingletonObjects() : attributeDataContainer{MAX_ATTRIBUTE_MESSAGE_RESPONSE_HISTORY}, attributeWriter{*this}, topology{*this}, restHandler{*this} {

    }
} /* namespace zigbee */

