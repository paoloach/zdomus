//
// Created by paolo on 27/12/16.
//

#include "JSZEndpoints.h"
#include "JSObjects.h"

using namespace v8;
using std::shared_ptr;

namespace zigbee {
    void JSZEndpoints::initJsObjectsTemplate(Isolate *isolate, Handle<ObjectTemplate> &global) {
        Local<String> jszEndpoints = String::NewFromUtf8(isolate, JSZENDPOINTS);

        Handle<Value> jszHandle = Handle<Value>::Cast(External::New(isolate, this));
        global->SetAccessor(jszEndpoints, JSZEndpoints::getZEndpoints, 0, jszHandle, ALL_CAN_READ, ReadOnly);
    }

    void JSZEndpoints::initJsObjectsInstance(Isolate *isolate) {
        Local<String> fnGetEndpointsWithCluster = String::NewFromUtf8(isolate, GET_ENDPOINTS_WITH_CLUSTER);

        Local<ObjectTemplate> objTemplate = ObjectTemplate::New();
        objTemplate->SetInternalFieldCount(1);
        objTemplate->Set(fnGetEndpointsWithCluster, FunctionTemplate::New(isolate, getEndpointsWithCluster));
        Local<Object> zDeviceInstanceLocal = objTemplate->NewInstance();
        zDeviceInstanceLocal->SetInternalField(0, External::New(isolate, this));

        zEndpointsInstance.Reset(isolate, zDeviceInstanceLocal);
    }

    JSZEndpoints *JSZEndpoints::getThis(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        return (JSZEndpoints *) wrap->Value();
    }

    void JSZEndpoints::getZEndpoints(Local<String>, const PropertyCallbackInfo<Value> &info) {
        Local<Value> self = info.Data();
        Local<External> wrap = Local<External>::Cast(self);
        void *ptr = wrap->Value();
        JSZEndpoints *This = (JSZEndpoints *) (ptr);

        Local<Object> zDeviceInstanceLocal = Local<Object>::New(info.GetIsolate(), This->zEndpointsInstance);

        info.GetReturnValue().Set(zDeviceInstanceLocal);
    }

    void JSZEndpoints::getEndpointsWithCluster(const v8::FunctionCallbackInfo<v8::Value> &info) {
        JSZEndpoints *This = getThis(info);

       // info.GetReturnValue().Set(This->zDevices->getNumDevices());
    }
}