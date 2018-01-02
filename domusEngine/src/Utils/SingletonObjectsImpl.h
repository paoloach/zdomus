/*
 * SingletonObjects.h
 *
 *  Created on: 19/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_UTILS_SINGLETONOBJECTS_IMPL_H_
#define SRC_UTILS_SINGLETONOBJECTS_IMPL_H_

#include <boost/asio/io_service.hpp>
#include <memory>
#include <zigbee/ZigbeeDevice.h>
#include "../ZigbeeData/BindTable.h"
#include "Clusters.h"
#include "AttributeWriter.h"
#include "Constant.h"
#include "../ZigbeeData/TopologyCreation.h"
#include "DeviceInfoDispatcher.h"
#include "../httpServer/RestHandlerImpl.h"
#include "DriverFactory.h"
#include "SingletonObjects.h"

struct libusb_context;

namespace zigbee {


    class ClusterTypeFactory;

    class ZDevices;

    class Configuration;

    class JSManager;

    class AttributeWriter;

    class SingletonObjectsImpl : public SingletonObjects {
    public:
        SingletonObjectsImpl();

        SingletonObjectsImpl(std::string &&configurationFileName, std::string  driverName, std::vector<DriverFactory *> && driverFactories);

        virtual ~SingletonObjectsImpl() = default;

    public:
        virtual ZigbeeDevice* getZigbeeDevice() override { return zigbeeDevice.get(); }

        virtual ZDevices * getZDevices() override { return zDevices.get(); }

        virtual Configuration * getConfiguration() override { return configuration.get(); }

        virtual JSManager *  getJSManager() override { return jsManager.get(); }

        virtual BindTable  * getBindTable() override { return &bindTable; }

        virtual Clusters * getClusters() override { return &clusters; };

        virtual AttributeWriter * getAttributeWriter() override { return &attributeWriter; }

        virtual DeviceInfoDispatcher * getDeviceInfoDispatcher() override {return &deviceInfoDispatcher;}

        virtual Constant * getConstant() override {return &constant;}

        virtual TopologyCreation * getTopology()override  {return &topology;}

        virtual http::RestHandler * getRestHandler() override {return &restHandler;}

    private:
        boost::asio::io_service io;
        std::unique_ptr<ZDevices> zDevices;
        std::unique_ptr<ZigbeeDevice> zigbeeDevice;
        std::unique_ptr<Configuration> configuration;
        std::unique_ptr<JSManager> jsManager;
        DeviceInfoDispatcher deviceInfoDispatcher;
        BindTable bindTable;
        Clusters clusters;
        AttributeWriter attributeWriter;
        Constant constant;
        TopologyCreation topology;
        http::RestHandlerImpl restHandler;
    };

} /* namespace zigbee */

#endif /* SRC_UTILS_SINGLETONOBJECTS_H_ */
