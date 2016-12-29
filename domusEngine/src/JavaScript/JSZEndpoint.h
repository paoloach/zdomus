/*
 * JSZEndpoint.h
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZENDPOINT_H_
#define SRC_JAVASCRIPT_JSZENDPOINT_H_

#include <v8.h>
#include <memory>
#include <zigbee/EndpointID.h>

#include "../ZigbeeData/ZDevices.h"
#include "JSZDevice.h"


namespace zigbee {

    class JSZDevice;

    class JSZCluster;

    class JSZEndpoint {
    public:
        JSZEndpoint() = default;

        JSZEndpoint(ZDevices *zDevices, JSZCluster *jsZCluster);

        virtual ~JSZEndpoint() = default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, const ExtAddress &extAddress, EndpointID endpointId);

        virtual void resetPersistences();

    private:
        void static constructor(const v8::FunctionCallbackInfo<v8::Value> &info);

        void static jsEndpointId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

        void static jsProfileId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

        void static jsDeviceId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

        void static jsDeviceVersion(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

        void static jsNetworkId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

        void static jsGetCluster(const v8::FunctionCallbackInfo<v8::Value> &info);

        static ExtAddress *getExtAddress(const v8::PropertyCallbackInfo<v8::Value> &info);

        static ExtAddress *getExtAddress(const v8::FunctionCallbackInfo<v8::Value> &info);

        static ZDevices *getZDevices(const v8::PropertyCallbackInfo<v8::Value> &info);

        static uint32_t getEndpointId(const v8::PropertyCallbackInfo<v8::Value> &info);

        static uint32_t getEndpointId(const v8::FunctionCallbackInfo<v8::Value> &info);

        static JSZEndpoint *getThis(const v8::FunctionCallbackInfo<v8::Value> &info);

        static ZDevices *getZDevices(const v8::FunctionCallbackInfo<v8::Value> &info);

        static ExtAddress getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info, int index);

        static void checkConstructorValidArgument(v8::Isolate *isolate, const v8::FunctionCallbackInfo<v8::Value> &info);

        static ZEndpoint getZEndpoint(const v8::PropertyCallbackInfo<v8::Value> &info);

        std::shared_ptr<ExtAddress> getPersistenceExtAddress(const ExtAddress &extAddress);

    private:
        ZDevices_P zDevices;
        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
        std::map<ExtAddress, std::shared_ptr<ExtAddress> > usedExtAddresses;
        JSZCluster *jsZCluster;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZENDPOINT_H_ */
