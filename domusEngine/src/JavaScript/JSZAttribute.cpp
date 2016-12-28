/*
 * JSZAttribute.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>
#include "JSZAttribute.h"
#include <zcl/ZCLAttribute.h>
#include <zcl/ClusterTypeFactory.h>
#include "JSObjects.h"
#include "Exceptions/JSException.h"
#include "Exceptions/JSExceptionNoDevice.h"
#include "Exceptions/JSExceptionNoEndpoint.h"
#include "Exceptions/JSExceptionNoInCluster.h"
#include "Exceptions/JSExceptionNoAttribute.h"
#include "Exceptions/JSExceptionInvalidAttributeType.h"
#include "Exceptions/JSExceptionArgNoFunction.h"
#include "../ZigbeeData/ZDevices.h"

using namespace v8;
using std::stringstream;
using std::get;
using std::shared_ptr;

namespace zigbee {


    std::map<ZCLAttribute::Status, std::string> JSZAttribute::statusMap = {{ZCLAttribute::Available,    "available"},
                                                                           {ZCLAttribute::NotAvailable, "notAvailable"},
                                                                           {
                                                                            ZCLAttribute::NotSupported, "notSupported"},
                                                                           {ZCLAttribute::Requesting,   "requesting"},
                                                                           {ZCLAttribute::Undefined,    "undefined"},};

    JSZAttribute::JSZAttribute(SingletonObjects * singletonObjects, ZCLTypeDataType zclType) :
            singletonObjects(singletonObjects), zclType(zclType) {
    }

    JSZAttribute::~JSZAttribute() {
        for (auto &function: mapFunction) {
            CallbackData callback = function.second;
            auto attribute = get<1>(callback);
            attribute->removeOnChangeListener(get<0>(callback));
            get<2>(callback).Reset();
        }

    }

    void JSZAttribute::initJsObjectsTemplate(v8::Isolate *isolate,
                                             const v8::Local<v8::FunctionTemplate> &zAttributeFunctionTemplate) {
        Local<String> requestValueMethod = String::NewFromUtf8(isolate, REQUEST_VALUE);
        Local<String> isAvailableMethod = String::NewFromUtf8(isolate, IS_AVAILABLE);
        Local<String> isUnsupportedMethod = String::NewFromUtf8(isolate, IS_UNSUPPORTED);
        Local<String> getStatusMethod = String::NewFromUtf8(isolate, GET_STATUS);
        Local<String> getIdentifierMethod = String::NewFromUtf8(isolate, GET_IDENTIFIER);
        Local<String> getNameMethod = String::NewFromUtf8(isolate, GET_NAME);
        Local<String> isReadOnlyMethod = String::NewFromUtf8(isolate, IS_READONLY);

        Local<ObjectTemplate> zAttributeClusterInstanceTemplate = zAttributeFunctionTemplate->InstanceTemplate();

        zAttributeClusterInstanceTemplate->Set(requestValueMethod, FunctionTemplate::New(isolate, jsRequestValue));

        zAttributeClusterInstanceTemplate->Set(isAvailableMethod, FunctionTemplate::New(isolate, jsIsAvailable));
        zAttributeClusterInstanceTemplate->Set(isUnsupportedMethod, FunctionTemplate::New(isolate, jsIsUnsupported));
        zAttributeClusterInstanceTemplate->Set(getStatusMethod, FunctionTemplate::New(isolate, jsGetStatus));
        zAttributeClusterInstanceTemplate->Set(getIdentifierMethod, FunctionTemplate::New(isolate, jsGetIdentifier));
        zAttributeClusterInstanceTemplate->Set(getNameMethod, FunctionTemplate::New(isolate, jsGetName));
        zAttributeClusterInstanceTemplate->Set(isReadOnlyMethod, FunctionTemplate::New(isolate, jsIsReadOnly));
    }

    void JSZAttribute::validateParams(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 4) {
            throw JSException("Invalid params: expected 4 (extended address, endpoint id, cluster id, attribute id)");
        }
    }

    v8::Local<v8::Object>
    JSZAttribute::createInstance(v8::Isolate *isolate, std::shared_ptr<ZCLAttribute> &zclAttribute) {
        if (zclAttribute->getZCLType() != getZCLType()) {
            throw JSExceptionInvalidAttributeType(getName(), zclAttribute->getZCLType(), getZCLType());
        }
        Local<ObjectTemplate> zAttributeT = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> zAttributeInstance = zAttributeT->NewInstance();

        zAttributeInstance->SetInternalField(0, External::New(isolate, zclAttribute.get()));
        zAttributeInstance->SetInternalField(1, External::New(isolate, this));
        return zAttributeInstance;
    }

    void JSZAttribute::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            validateParams(info);
            ExtAddress extAddress = getExtAddressFromArg(info);
            EndpointID endpointId(info[1].As<v8::Integer>()->Value());
            ClusterID clusterId(info[2].As<v8::Integer>()->Value());
            uint32_t attributeId = info[3].As<v8::Integer>()->Value();
            JSZAttribute *This = (JSZAttribute *) (Local<External>::Cast(info.Data())->Value());

            std::shared_ptr<ZCLAttribute> zclAttribute = This->getZCLAttribute(extAddress, endpointId, clusterId,
                                                                               attributeId);

            info.GetReturnValue().Set(This->createInstance(isolate, zclAttribute));
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    ExtAddress JSZAttribute::getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info) {
        v8::String::Utf8Value extAddressString(info[0]);
        std::stringstream stream{*extAddressString};
        ExtAddress extAddress{};
        stream >> extAddress;
        return extAddress;
    }

    void JSZAttribute::jsRequestValue(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<Object> self = info.Holder();
            Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
            auto attribute = (ZCLAttribute *) wrap->Value();
            if (info.Length() == 1) {
                if (!info[0]->IsFunction()) {
                    throw JSExceptionArgNoFunction(0);
                }
                Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
                JSZAttribute *This = (JSZAttribute *) wrap->Value();

                v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>> persistenteObject;
                persistenteObject.Reset(isolate, info[0]);

                Local<Function> callback = Local<Function>::Cast(info[0]);
                int identity = callback->GetIdentityHash();
                auto cluster = attribute->getClusterParent();
                JsCallbackParameters callbackParameters;
                if (cluster != nullptr) {
                    callbackParameters.nwkAddr = cluster->getNetworkAddress();
                    callbackParameters.endpointID = cluster->getEndpoint();
                    callbackParameters.clusterID = cluster->getId();
                }
                callbackParameters.attributeId = attribute->getIdentifier();
                auto con = attribute->onChange([This, isolate, identity, callbackParameters]() {
                    This->changeSignalCallback(isolate, identity, callbackParameters);
                });
                std::lock_guard<std::mutex> lock(This->mapFunctionMutex);
                This->mapFunction.insert({identity, std::make_tuple(con, attribute, persistenteObject)});
            }
            attribute->requestValue();
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void
    JSZAttribute::changeSignalCallback(v8::Isolate *isolate, int identity, JsCallbackParameters callbackParameters) {
        if (mapFunction.count(identity) > 0) {
            CallbackData callbackData = popCallbackData(identity);
            Local<Value> object = Local<Value>::New(isolate, std::get<2>(callbackData));
            Local<Function> callback = Local<Function>::Cast(object);
            String::Utf8Value name(callback->GetInferredName());

            Local<Value> argv[4];
            argv[0] = v8::Int32::New(isolate, callbackParameters.nwkAddr.getId());
            argv[1] = v8::Int32::New(isolate, callbackParameters.endpointID.getId());
            argv[2] = v8::Int32::New(isolate, callbackParameters.clusterID.getId());
            argv[3] = v8::Int32::New(isolate, callbackParameters.attributeId);

            callback->CallAsFunction(object, 4, argv);
            get<1>(callbackData)->removeOnChangeListener(get<0>(callbackData));
            get<2>(callbackData).Reset();
        }
    }

    void JSZAttribute::jsIsAvailable(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            info.GetReturnValue().Set(attribute->isAvailable());
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::jsIsUnsupported(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            info.GetReturnValue().Set(attribute->isUnsupported());
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::jsGetStatus(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            ZCLAttribute::Status status = attribute->getStatus();
            Local<String> name = String::NewFromUtf8(isolate, statusMap[status].c_str());
            info.GetReturnValue().Set(name);
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::jsGetIdentifier(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            info.GetReturnValue().Set(attribute->getIdentifier());
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::jsGetName(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            Local<String> name = String::NewFromUtf8(isolate, attribute->getName().data());
            info.GetReturnValue().Set(name);
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::jsIsReadOnly(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
            ZCLAttribute *attribute = (ZCLAttribute *) wrap->Value();
            info.GetReturnValue().Set(attribute->isReadOnly());
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZAttribute::resetPersistence() {
        functionTemplate.Reset();
    }

    std::shared_ptr<ZCLAttribute>
    JSZAttribute::getZCLAttribute(const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId,
                                  uint32_t attributeId) {
        if (!singletonObjects->getZDevices()->exists(extAddress)) {
            throw JSExceptionNoDevice(extAddress);
        }
        auto zDevice = singletonObjects->getZDevices()->getDevice(extAddress);
        if (!zDevice->isEndpointPresents(endpointId)) {
            throw JSExceptionNoEndpoint(extAddress, endpointId);
        }
        ZEndpoint zEndpoint = zDevice->getEndpoint(endpointId);
        if (!zEndpoint.hasInCluster(clusterId)) {
            throw JSExceptionNoInCluster(extAddress, endpointId, clusterId);
        }
        std::shared_ptr<Cluster> cluster = singletonObjects->getClusters()->getCluster(zDevice->getNwkAddr(),endpointId, clusterId);
        std::shared_ptr<ZCLAttribute> attribute = cluster->getAttribute(attributeId);
        if (!attribute) {
            throw JSExceptionNoAttribute(extAddress, endpointId, clusterId, attributeId);
        }
        return attribute;
    }

    JSZAttribute::CallbackData JSZAttribute::popCallbackData(int id) {
        std::lock_guard<std::mutex> lock(mapFunctionMutex);
        CallbackData callbackData = std::move(mapFunction[id]);
        mapFunction.erase(id);
        return callbackData;
    }

} /* namespace zigbee */
