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
#include <any>
#include <zcl/ZCLAttribute.h>
#include "v8.h"
#include "../ZigbeeData/ExtAddress.h"
#include <zcl/Cluster.h>
#include "../Utils/SingletonObjects.h"
#include "JSCallbackFifo.h"


namespace zigbee {

    class ZigbeeDevice;

    class ZDevices;

    class ZCLAttribute;

    class ClusterTypeFactory;


    class JSZAttribute {
    protected:
        struct JSZAttributeCallback : public ResponseCallback<ZCLAttribute *> {
            v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>> persistentCallback;
            JSCallbackFifo *callbackFifo;
            v8::Isolate *isolate;

            JSZAttributeCallback(v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>> object, JSCallbackFifo *callbackFifo, v8::Isolate *isolate)
                    : persistentCallback(object), callbackFifo(callbackFifo), isolate(isolate) {}

            void response(ZCLAttribute *attribute) override;

            void timeout() override;
        };

    public:
        static std::map<ZCLAttribute::Status, std::string> statusMap;
        using CallbackData = std::tuple<std::list<std::function<void()>>::iterator, ZCLAttribute *, v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>>>;
    public:
        JSZAttribute(SingletonObjects *singletonObjects, JSCallbackFifo &jsCallbackFifo, ZCLTypeDataType zclType) : singletonObjects(singletonObjects),
                                                                                                                    callbackFifo(jsCallbackFifo), zclType(zclType) {}

        virtual ~JSZAttribute() = default;

        ZCLTypeDataType getZCLType() {
            return zclType;
        }

        ZCLAttribute *getZCLAttribute(const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId, uint32_t attributeId);

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) = 0;

        virtual std::string getName() const = 0;

        virtual void resetPersistence();

        v8::Local<v8::Object> createInstance(v8::Isolate *isolate, ZCLAttribute *zclAttribute);

    protected:
        static void constructor(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void jsValue(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info);

        static void setJSValue(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info);

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

        static JSZAttribute * getThis(const v8::FunctionCallbackInfo<v8::Value> &info);

    protected:
        SingletonObjects *singletonObjects;

        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
        std::map<ExtAddress, std::shared_ptr<ExtAddress> > usedExtAddresses;
        JSCallbackFifo &callbackFifo;
        ZCLTypeDataType zclType;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTE_H_ */
