/*
 * JSZEndpoint.cpp
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSObjects.h"
#include "JSZEndpoint.h"
#include "JSZCluster.h"
#include "Exceptions/JSExceptionNoDevice.h"
#include "Exceptions/JSExceptionNoEndpoint.h"
#include "Exceptions/JSExceptionArgNoUInteger.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "Exceptions/JSExceptionOnlyTwoArguments.h"

using namespace v8;
using std::shared_ptr;

namespace zigbee {

    JSZEndpoint::JSZEndpoint(ZDevices *zDevices, JSZCluster *jsZCluster) : zDevices(zDevices), jsZCluster(jsZCluster) {
    }

    void JSZEndpoint::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> jszEndpointClassName = String::NewFromUtf8(isolate, JSZENDPOINT);
        // attributes
        Local<String> endpointIdAttribute = String::NewFromUtf8(isolate, ENDPOINT);
        Local<String> profileIdAttribute = String::NewFromUtf8(isolate, PROFILEID);
        Local<String> deviceIdAttribute = String::NewFromUtf8(isolate, DEVICEID);
        Local<String> deviceVersionAttribute = String::NewFromUtf8(isolate, DEVICE_VERSION);
        Local<String> networkIdAttribute = String::NewFromUtf8(isolate, NETWORK_ID);
        // methods
        Local<String> getClusterMethod = String::NewFromUtf8(isolate, GET_CLUSTER);

        Local<FunctionTemplate> zEndpoinFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        zEndpoinFunctionTemplate->SetClassName(jszEndpointClassName);
        Local<ObjectTemplate> zEndpoinInstanceTemplate = zEndpoinFunctionTemplate->InstanceTemplate();

        zEndpoinInstanceTemplate->SetInternalFieldCount(4);
        // attributes
        zEndpoinInstanceTemplate->SetAccessor(endpointIdAttribute, jsEndpointId, nullptr, Handle<Value>(), ALL_CAN_READ, ReadOnly);
        zEndpoinInstanceTemplate->SetAccessor(profileIdAttribute, jsProfileId, nullptr, Handle<Value>(), ALL_CAN_READ, ReadOnly);
        zEndpoinInstanceTemplate->SetAccessor(deviceIdAttribute, jsDeviceId, nullptr, Handle<Value>(), ALL_CAN_READ, ReadOnly);
        zEndpoinInstanceTemplate->SetAccessor(deviceVersionAttribute, jsDeviceVersion, nullptr, Handle<Value>(), ALL_CAN_READ, ReadOnly);
        zEndpoinInstanceTemplate->SetAccessor(networkIdAttribute, jsNetworkId, nullptr, Handle<Value>(), ALL_CAN_READ, ReadOnly);
        zEndpoinInstanceTemplate->Set(getClusterMethod, FunctionTemplate::New(isolate, jsGetCluster));
        // functions
        global->Set(jszEndpointClassName, zEndpoinFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, zEndpoinFunctionTemplate);
    }

    v8::Local<v8::Object> JSZEndpoint::createInstance(v8::Isolate *isolate, const ExtAddress &extAddress, EndpointID endpointId) {
        if (!zDevices->exists(extAddress)) {
            throw JSExceptionNoDevice(extAddress);
        }
        auto zDevice = zDevices->getDevice(extAddress);
        if (!zDevice->isEndpointPresents(endpointId)) {
            throw JSExceptionNoEndpoint(extAddress, endpointId);
        }

        Local<ObjectTemplate> zEndpointTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> zEndpointInstance = zEndpointTemplate->NewInstance();
        std::shared_ptr<ExtAddress> usedAddr = getPersistenceExtAddress(extAddress);
        zEndpointInstance->SetInternalField(0, External::New(isolate, usedAddr.get()));
        zEndpointInstance->SetInternalField(1, External::New(isolate, zDevices));
        zEndpointInstance->SetInternalField(2, Uint32::New(isolate, endpointId.getId()));
        zEndpointInstance->SetInternalField(3, External::New(isolate, this));
        return zEndpointInstance;
    }

    void JSZEndpoint::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            checkConstructorValidArgument(isolate, info);
            JSZEndpoint *This = (JSZEndpoint *) (Local<External>::Cast(info.Data())->Value());
            ExtAddress extAddress = getExtAddressFromArg(info, 0);
            uint32_t endpointId = info[1].As<v8::Integer>()->Value();

            info.GetReturnValue().Set(This->createInstance(info.GetIsolate(), extAddress, EndpointID(endpointId)));
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    ExtAddress JSZEndpoint::getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info, int index) {
        v8::String::Utf8Value extAddressString(info[index]);
        std::stringstream stream{*extAddressString};
        ExtAddress extAddress{};
        stream >> extAddress;
        return extAddress;
    }

    void JSZEndpoint::checkConstructorValidArgument(v8::Isolate *, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 2) {
            throw JSExceptionOnlyTwoArguments(JSZENDPOINT);
        }
        Local<Value> arg0 = info[0];
        if (!arg0->IsString()) {
            throw JSExceptionArgNoString(JSZENDPOINT, 0, true);
        }
        Local<Value> arg1 = info[1];
        if (!arg1->IsUint32()) {
            throw JSExceptionArgNoUInteger(JSZENDPOINT, 0);
        }
    }

    void JSZEndpoint::jsGetCluster(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            if (info.Length() != 1 || !info[0]->IsUint32()) {
                std::stringstream stream;
                stream << GET_CLUSTER << " needs only one argument: an integer for the cluster";
                throw JSException(stream.str());
            }
            std::vector<uint8_t> data;
            JSZEndpoint *This = getThis(info);
            uint32_t clusterId = info[0]->ToUint32()->Value();
            ExtAddress *extAddress = getExtAddress(info);
            uint32_t endpointID = getEndpointId(info);
            Local<Object> cluster = This->jsZCluster->createInstance(isolate, *extAddress, EndpointID{(int)endpointID}, ClusterID{(int)clusterId});
            info.GetReturnValue().Set(cluster);

        } catch (JSException &jsException) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZEndpoint::jsEndpointId(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
        uint32_t endpointId = getEndpointId(info);
        info.GetReturnValue().Set(endpointId);
    }

    void JSZEndpoint::jsProfileId(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
        ZEndpoint zEndpoint = getZEndpoint(info);
        info.GetReturnValue().Set(zEndpoint.getAppProfId());
    }

    void JSZEndpoint::jsDeviceId(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
        ZEndpoint zEndpoint = getZEndpoint(info);
        info.GetReturnValue().Set(zEndpoint.getAppDeviceId());
    }

    void JSZEndpoint::jsDeviceVersion(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
        ZEndpoint zEndpoint = getZEndpoint(info);
        info.GetReturnValue().Set(zEndpoint.getAppDevVer());
    }

    void JSZEndpoint::jsNetworkId(v8::Local<v8::String> , const v8::PropertyCallbackInfo<v8::Value> &info) {
        ExtAddress *extAddress = getExtAddress(info);
        ZDevices *zDevices = getZDevices(info);
        auto zDevice = zDevices->getDevice(*extAddress);
        info.GetReturnValue().Set(zDevice->getNwkAddr().getId());
    }

    ZEndpoint JSZEndpoint::getZEndpoint(const v8::PropertyCallbackInfo<v8::Value> &info) {
        ExtAddress *extAddress = getExtAddress(info);
        ZDevices *zDevices = getZDevices(info);
        auto zDevice = zDevices->getDevice(*extAddress);
        EndpointID endpointId(getEndpointId(info));
        return zDevice->getEndpoint(endpointId);
    }

    std::shared_ptr<ExtAddress> JSZEndpoint::getPersistenceExtAddress(const ExtAddress &extAddress) {
        std::shared_ptr<ExtAddress> usedAddr{};
        if (usedExtAddresses.count(extAddress) == 0) {
            usedAddr = std::make_shared<ExtAddress>(extAddress);
            usedExtAddresses[extAddress] = usedAddr;
        } else {
            usedAddr = usedExtAddresses[extAddress];
        }
        return usedAddr;
    }

    ExtAddress *JSZEndpoint::getExtAddress(const v8::PropertyCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        return (ExtAddress *) wrap->Value();
    }

    ExtAddress *JSZEndpoint::getExtAddress(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        return (ExtAddress *) wrap->Value();
    }

    ZDevices *JSZEndpoint::getZDevices(const v8::PropertyCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
        return (ZDevices *) wrap->Value();
    }

    uint32_t JSZEndpoint::getEndpointId(const v8::PropertyCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<Integer> endpointId = self->GetInternalField(2).As<Integer>();
        return endpointId->Value();
    }

    uint32_t JSZEndpoint::getEndpointId(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<Integer> endpointId = self->GetInternalField(2).As<Integer>();
        return endpointId->Value();
    }

    void JSZEndpoint::resetPersistences() {
        functionTemplate.Reset();
    }

    ZDevices *JSZEndpoint::getZDevices(const v8::FunctionCallbackInfo<v8::Value> &) {
        return nullptr;
    }

    JSZEndpoint *JSZEndpoint::getThis(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(3));
        return (JSZEndpoint *) wrap->Value();
    }
} /* namespace zigbee */

