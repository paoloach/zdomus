/*
 * JSZAttribute.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTE_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTE_H_


#include <memory>
#include <mutex>
#include <map>
#include <set>
#include <tuple>
#include <zcl/ZCLAttribute.h>
#include "v8.h"
#include "../ZigbeeData/ExtAddress.h"


namespace zigbee {

    class ZigbeeDevice;
    class ZDevices;
    class ZCLAttribute;
    class ClusterTypeFactory;

    class JSZAttribute {
    protected:
        struct JsCallbackParameters {
            NwkAddr nwkAddr;
            EndpointID endpointID;
            ClusterID clusterID;
            ZigbeeAttributeId  attributeId;
        };
    public:
        static std::map<ZCLAttribute::Status, std::string> statusMap;
        using CallbackData = std::tuple<std::list<std::function<void()>>::iterator, ZCLAttribute *, v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>>>;
    public:
        JSZAttribute( ZDevices * zDevices, const std::shared_ptr<ZigbeeDevice> &zigbeeDevice,
                     const std::shared_ptr<ClusterTypeFactory> &clusterFactory,ZCLTypeDataType zclType);
        virtual ~JSZAttribute();
        ZCLTypeDataType getZCLType() {
            return zclType;
        }
        std::shared_ptr<ZCLAttribute> getZCLAttribute(const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId, uint32_t attributeId);
    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) = 0;
        virtual std::string getName() const = 0;
        virtual void resetPersistence();
        v8::Local<v8::Object> createInstance(v8::Isolate *isolate, std::shared_ptr<ZCLAttribute> &zclAttribute);
    protected:
        static void constructor(const v8::FunctionCallbackInfo<v8::Value> &info);
        static ExtAddress getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void validateParams(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsRequestValue(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsIsAvailable(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsIsUnsupported(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsGetStatus(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsGetIdentifier(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsGetName(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void jsIsReadOnly(const v8::FunctionCallbackInfo<v8::Value> &info);
        void initJsObjectsTemplate(v8::Isolate *isolate, const v8::Local<v8::FunctionTemplate> &zAttributeFunctionTemplate);


        void changeSignalCallback(v8::Isolate *isolate, int identity,JsCallbackParameters callbackParameters);
        CallbackData popCallbackData(int id);
    protected:
        ZDevices * zDevices;
        std::shared_ptr<ZigbeeDevice> zigbeeDevice;
        std::shared_ptr<ClusterTypeFactory> clusterFactory;

        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
        std::map<ExtAddress, std::shared_ptr<ExtAddress> > usedExtAddresses;
        std::map<int, CallbackData> mapFunction;
        std::mutex mapFunctionMutex;
        ZCLTypeDataType zclType;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTE_H_ */
