//
// Created by paolo on 27/12/16.
//

#include "../ZigbeeData/ZDevices.h"
#include "JSZEndpoints.h"
#include "JSZEndpoint.h"
#include "JSObjects.h"
#include "Exceptions/JSExceptionOnlyOneArgument.h"
#include "Exceptions/JSExceptionArgNoUInteger.h"

using namespace v8;
using std::shared_ptr;

namespace zigbee {
    void JSZEndpoints::initJsObjectsTemplate(Isolate *isolate, Handle<ObjectTemplate> &global) {
        Local<String> jszEndpoints = String::NewFromUtf8(isolate, JSZENDPOINTS);

        Handle<Value> jszHandle = Handle<Value>::Cast(External::New(isolate, this));
        global->SetAccessor(jszEndpoints, JSZEndpoints::getZEndpoints, 0, jszHandle, ALL_CAN_READ, ReadOnly);
    }

    void JSZEndpoints::initJsObjectsInstance(Isolate *isolate) {
        Local<String> fnGetEndpointsWithCluster = String::NewFromUtf8(isolate, GET_ENDPOINTS_WITH_IN_CLUSTER);

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
        if (info.Length() != 1) {
            throw JSExceptionOnlyOneArgument(GET_ENDPOINTS_WITH_IN_CLUSTER);
        }

        Local<Value> arg0 = info[0];
        if (!arg0->IsUint32()){
            throw JSExceptionArgNoUInteger(GET_ENDPOINTS_WITH_IN_CLUSTER);
        }

        ClusterID clusterId { arg0->Int32Value()};
        ZDevices *  zDevices = This->singletonObjects->getZDevices();
        Isolate * isolate = info.GetIsolate();
        std::vector<Local<Object>> endpoints;
        for (auto & device: zDevices->getDevices()){
            for (auto & endpoint: device->getEndpoints()){
                if (endpoint.second.hasInCluster(clusterId)){
                    endpoints.push_back(This->jszEndpoint->createInstance(isolate, device->getExtAddr(), endpoint.first));
                };
            }
        }


        auto result = Array::New(isolate, endpoints.size());
        int index=0;
        for(auto & endpoint: endpoints){
            result->Set(index, endpoint);
            index++;
        }

        info.GetReturnValue().Set(result);
    }

    void JSZEndpoints::resetInstance() {
        zEndpointsInstance.Reset();
    }
}