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
#include "../IO/AttributeDataContainer.h"
#include "../ZigbeeData/BindTable.h"
#include "../usb/AttributeValuesSignalMap.h"
#include "Clusters.h"
#include "AttributeWriter.h"
#include "Constant.h"

struct libusb_context;

namespace zigbee {

    namespace http {
        class FixedPathContainer;
    }
    class ClusterTypeFactory;

    class ZigbeeDevice;

    class ZDevices;

    class Configuration;

    class JSManager;

    class AttributeDataContainer;

    class AttributeWriter;

    class DeviceInfoDispatcher;

    class SingletonObjects {
    public:
        SingletonObjects();

        SingletonObjects(std::string &&configurationFileName, bool demo);

        virtual ~SingletonObjects() = default;

    public:
        virtual std::shared_ptr<ZigbeeDevice> getZigbeeDevice() { return zigbeeDevice; }

        virtual std::shared_ptr<ZDevices> getZDevices() { return zDevices; }

        virtual std::shared_ptr<Configuration> getConfiguration() { return configuration; }

        virtual std::shared_ptr<JSManager> getJSManage() { return jsManager; }

        virtual std::shared_ptr<http::FixedPathContainer> getFixedPathContainer() { return fixedPathContainer; }

        virtual boost::asio::io_service &getIO() { return io; }

        virtual AttributeDataContainer &getAttributeDataContainer() { return attributeDataContainer; }

        virtual BindTable &getBindTable() { return bindTable; }

        virtual AttributeValueSignalMap &getAttributeValueSignalMap() { return attributeValueSignalMap; }

        virtual std::shared_ptr<Clusters> getClusters() { return clusters; };

        virtual AttributeWriter &getAttributeWriter() { return attributeWriter; }

        virtual std::shared_ptr<DeviceInfoDispatcher> getDeviceInfoDispatcher() {return deviceInfoDispatcher;}

        virtual Constant & getConstant() {return constant;}


    private:
        boost::asio::io_service io;
        std::shared_ptr<ZDevices> zDevices;
        std::shared_ptr<ZigbeeDevice> zigbeeDevice;
        std::shared_ptr<Configuration> configuration;
        std::shared_ptr<JSManager> jsManager;
        std::shared_ptr<DeviceInfoDispatcher> deviceInfoDispatcher;
        BindTable bindTable;
        zigbee::AttributeDataContainer attributeDataContainer;
        libusb_context *usbContext;
        std::shared_ptr<http::FixedPathContainer> fixedPathContainer;
        AttributeValueSignalMap attributeValueSignalMap;
        std::shared_ptr<Clusters> clusters;
        AttributeWriter attributeWriter;
        Constant constant;
    };

} /* namespace zigbee */

#endif /* SRC_UTILS_SINGLETONOBJECTS_H_ */
