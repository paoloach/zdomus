/*
 * JSZCluster.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZCLUSTER_H_
#define SRC_JAVASCRIPT_JSZCLUSTER_H_

#include <v8.h>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <memory>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zcl/CmdParams/ClusterCmdParams.h>

#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/ZDevices.h"
#include "JSZDevice.h"
#include "../ZigbeeData/ExtAddress.h"


namespace zigbee {

    class ZigbeeDevice;

    class ZDevices;

    class JSZEndpoint;

    class JSZAttributeFactory;

    class JSZCluster {
    private:
        typedef boost::tuple<NwkAddr, EndpointID, ClusterID> Key;
        typedef v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>> PersistenceObject;
        typedef boost::tuple<PersistenceObject, std::shared_ptr<Cluster> > Value;
    public:
        JSZCluster() = default;

        JSZCluster(JSZAttributeFactory *jsZAttributeFactory, SingletonObjects *singletonObjects);

        virtual ~JSZCluster() = default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId);

        virtual void resetPersistences();

    protected:
        static void constructor(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void jsGetPropertyById(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void jsExecuteCmdById(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void checkConstructorValidArgument(v8::Isolate *isolate, const v8::FunctionCallbackInfo<v8::Value> &info);

        static ExtAddress getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info, int index);

        std::shared_ptr<ExtAddress> getPersistenceExtAddress(const ExtAddress &extAddress);

        static Cluster *getCluster(const v8::FunctionCallbackInfo<v8::Value> &info);

        static JSZCluster *getThis(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void checkArgument(const v8::FunctionCallbackInfo<v8::Value> &info, unsigned int index, const std::shared_ptr<ClusterCmdParamsBase> &cmdParam);

        static std::vector<uint8_t> addArgument(v8::Local<v8::Value> value, const std::shared_ptr<ClusterCmdParamsBase> &cmdParam);

        static void checkIdCmd(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void weakCallback(const v8::WeakCallbackInfo<JSZCluster> &data);

    private:
        SingletonObjects *singletonObjects;
        JSZAttributeFactory *jsZAttributeFactory;
        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
        std::map<ExtAddress, std::shared_ptr<ExtAddress> > usedExtAddresses;
        std::map<Key, Value> usedCluster;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZCLUSTER_H_ */
