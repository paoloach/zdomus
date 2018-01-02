//
// Created by paolo on 02/01/18.
//

#ifndef DOMUS_ENGINE_SINGLETONOBJECT_H
#define DOMUS_ENGINE_SINGLETONOBJECT_H

#include <memory>

namespace zigbee {
    namespace http {
        class RestHandler;
    }
    class ClusterTypeFactory;

    class ZDevices;

    class Configuration;

    class JSManager;

    class AttributeWriter;

    class ZigbeeDevice;

    class Configuration;

    class BindTable;

    class Clusters;

    class DeviceInfoDispatcher;

    class Constant;

    class TopologyCreation;

    class SingletonObjects {
    public:
        SingletonObjects() {};

        virtual ~SingletonObjects() = default;

    public:
        virtual ZigbeeDevice *getZigbeeDevice() =0;

        virtual ZDevices *getZDevices() =0;

        virtual Configuration *getConfiguration() = 0;

        virtual JSManager *getJSManager() =0;

        virtual BindTable *getBindTable() = 0;

        virtual Clusters *getClusters() = 0;

        virtual AttributeWriter *getAttributeWriter() = 0;

        virtual DeviceInfoDispatcher *getDeviceInfoDispatcher() = 0;

        virtual Constant *getConstant() = 0;

        virtual TopologyCreation *getTopology() = 0;

        virtual http::RestHandler *getRestHandler()  = 0;
    };

}

#endif //DOMUS_ENGINE_SINGLETONOBJECT_H
