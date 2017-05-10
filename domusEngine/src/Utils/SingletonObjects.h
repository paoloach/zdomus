/*
 * SingletonObjects.h
 *
 *  Created on: 19/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_UTILS_SINGLETONOBJECTS_H_
#define SRC_UTILS_SINGLETONOBJECTS_H_

#include <boost/asio/io_service.hpp>
#include <memory>
#include <zigbee/ZigbeeDevice.h>
#include "../IO/AttributeDataContainer.h"
#include "../ZigbeeData/BindTable.h"
#include "../usb/AttributeValuesSignalMap.h"
#include "Clusters.h"
#include "AttributeWriter.h"
#include "Constant.h"
#include "../ZigbeeData/TopologyCreation.h"
#include "DeviceInfoDispatcher.h"
#include "../httpServer/RestHandler.h"
#include "HttpResponseEvent.h"

struct libusb_context;

namespace zigbee {


    class ClusterTypeFactory;

    class ZDevices;

    class Configuration;

    class JSManager;

    class AttributeDataContainer;

    class AttributeWriter;

    class SingletonObjects {
    public:
        SingletonObjects();

        SingletonObjects(std::string &&configurationFileName, std::string  driverName);

        virtual ~SingletonObjects() = default;

    public:
        virtual ZigbeeDevice* getZigbeeDevice() { return zigbeeDevice.get(); }

        virtual ZDevices * getZDevices() { return zDevices.get(); }

        virtual std::shared_ptr<Configuration> getConfiguration() { return configuration; }

        virtual std::shared_ptr<JSManager> getJSManage() { return jsManager; }

        virtual AttributeDataContainer &getAttributeDataContainer() { return attributeDataContainer; }

        virtual BindTable &getBindTable() { return bindTable; }

        virtual AttributeValueSignalMap &getAttributeValueSignalMap() { return attributeValueSignalMap; }

        virtual Clusters * getClusters() { return &clusters; };

        virtual AttributeWriter &getAttributeWriter() { return attributeWriter; }

        virtual DeviceInfoDispatcher * getDeviceInfoDispatcher() {return &deviceInfoDispatcher;}

        virtual Constant & getConstant() {return constant;}

        virtual TopologyCreation & getTopology() {return topology;}

        virtual http::RestHandler * getRestHandler() {return &restHandler;}

        virtual http::HttpResponseEvent * getHttpResponseEvent() {return &httpResponseEvent;}

    private:
        boost::asio::io_service io;
        std::unique_ptr<ZDevices> zDevices;
        std::unique_ptr<ZigbeeDevice> zigbeeDevice;
        std::shared_ptr<Configuration> configuration;
        std::shared_ptr<JSManager> jsManager;
        DeviceInfoDispatcher deviceInfoDispatcher;
        BindTable bindTable;
        zigbee::AttributeDataContainer attributeDataContainer;
        libusb_context *usbContext;
        AttributeValueSignalMap attributeValueSignalMap;
        Clusters clusters;
        AttributeWriter attributeWriter;
        Constant constant;
        TopologyCreation topology;
        http::RestHandler restHandler;
        http::HttpResponseEvent httpResponseEvent;
    };

} /* namespace zigbee */

#endif /* SRC_UTILS_SINGLETONOBJECTS_H_ */
