/*
 * JSZAttribute.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>
#include <boost/endian/conversion.hpp>
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
#include "../Utils/Clusters.h"

using namespace v8;
using std::stringstream;
using std::get;
using std::shared_ptr;
using std::make_tuple;
using std::tuple;
using std::any_cast;

namespace zigbee {


    std::map<ZCLAttribute::Status, std::string> JSZAttribute::statusMap = {{ZCLAttribute::Available,    "available"},
                                                                           {ZCLAttribute::NotAvailable, "notAvailable"},
                                                                           {ZCLAttribute::NotSupported, "notSupported"},
                                                                           {ZCLAttribute::Requesting,   "requesting"},
                                                                           {ZCLAttribute::Undefined,    "undefined"},};

    void JSZAttribute::initJsObjectsTemplate(v8::Isolate *isolate, const v8::Local<v8::FunctionTemplate> &zAttributeFunctionTemplate) {
        Local<String> requestValueMethod = String::NewFromUtf8(isolate, REQUEST_VALUE);
        Local<String> isAvailableMethod = String::NewFromUtf8(isolate, IS_AVAILABLE);
        Local<String> isUnsupportedMethod = String::NewFromUtf8(isolate, IS_UNSUPPORTED);
        Local<String> getStatusMethod = String::NewFromUtf8(isolate, GET_STATUS);
        Local<String> getIdentifierMethod = String::NewFromUtf8(isolate, GET_IDENTIFIER);
        Local<String> getNameMethod = String::NewFromUtf8(isolate, GET_NAME);
        Local<String> isReadOnlyMethod = String::NewFromUtf8(isolate, IS_READONLY);

        Local<String> valueProperty = String::NewFromUtf8(isolate, VALUE);

        Local<ObjectTemplate> zAttributeClusterInstanceTemplate = zAttributeFunctionTemplate->InstanceTemplate();

        zAttributeClusterInstanceTemplate->Set(requestValueMethod, FunctionTemplate::New(isolate, jsRequestValue));

        zAttributeClusterInstanceTemplate->Set(isAvailableMethod, FunctionTemplate::New(isolate, jsIsAvailable));
        zAttributeClusterInstanceTemplate->Set(isUnsupportedMethod, FunctionTemplate::New(isolate, jsIsUnsupported));
        zAttributeClusterInstanceTemplate->Set(getStatusMethod, FunctionTemplate::New(isolate, jsGetStatus));
        zAttributeClusterInstanceTemplate->Set(getIdentifierMethod, FunctionTemplate::New(isolate, jsGetIdentifier));
        zAttributeClusterInstanceTemplate->Set(getNameMethod, FunctionTemplate::New(isolate, jsGetName));
        zAttributeClusterInstanceTemplate->Set(isReadOnlyMethod, FunctionTemplate::New(isolate, jsIsReadOnly));

        zAttributeClusterInstanceTemplate->SetAccessor(valueProperty, jsValue, setJSValue, Handle<Value>(), ALL_CAN_READ, ReadOnly);
    }

    void JSZAttribute::validateParams(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 4) {
            throw JSException("Invalid params: expected 4 (extended address, endpoint id, cluster id, attribute id)");
        }
    }

    v8::Local<v8::Object> JSZAttribute::createInstance(v8::Isolate *isolate, ZCLAttribute *zclAttribute) {
        if (zclAttribute->getZCLType() != getZCLType()) {
            throw JSExceptionInvalidAttributeType(getName(), zclAttribute->getZCLType(), getZCLType());
        }
        Local<ObjectTemplate> zAttributeT = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> zAttributeInstance = zAttributeT->NewInstance();

        zAttributeInstance->SetInternalField(0, External::New(isolate, zclAttribute));
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

            ZCLAttribute *zclAttribute = This->getZCLAttribute(extAddress, endpointId, clusterId, attributeId);

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

    void JSZAttribute::setJSValue(v8::Local<v8::String> property, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &) {
        String::Utf8Value name(property);
        BOOST_LOG_TRIVIAL(info) << "Assign property: " << *name;
    }


    void JSZAttribute::jsValue(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            Local<Object> self = info.Holder();
            Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
            auto attribute = (ZCLAttribute *) wrap->Value();
            std::any value = attribute->getValue();
            switch (attribute->getZCLType()) {
                case ZCLTypeDataType::ZCLTypeStringChar: {
                    std::string sValue = any_cast<std::string>(value);
                    auto jsString = v8::String::NewFromUtf8(isolate, sValue.c_str());
                    info.GetReturnValue().Set(jsString);
                }
                    break;
                case ZCLTypeDataType::ZCLTypeBool:
                    info.GetReturnValue().Set(any_cast<bool>(value));
                    break;
                case ZCLTypeDataType::ZCLTypeSInt8:
                case ZCLTypeDataType::ZCLTypeSInt16:
                case ZCLTypeDataType::ZCLTypeSInt24:
                case ZCLTypeDataType::ZCLTypeSInt32:
                    info.GetReturnValue().Set(any_cast<int32_t>(value));
                    break;
                case ZCLTypeDataType::ZCLTypeSInt40:
                case ZCLTypeDataType::ZCLTypeSInt48:
                case ZCLTypeDataType::ZCLTypeSInt56:
                case ZCLTypeDataType::ZCLTypeSInt64:
                    info.GetReturnValue().Set(Integer::New(isolate, any_cast<double>(value)));
                    break;
                case ZCLTypeDataType::ZCLType8bitBitmap:
                case ZCLTypeDataType::ZCLTypeenum8:
                case ZCLTypeDataType::ZCLType16bitBitmap:
                case ZCLTypeDataType::ZCLTypeenum16:
                case ZCLTypeDataType::ZCLTypeUInt8:
                case ZCLTypeDataType::ZCLTypeUInt16:
                case ZCLTypeDataType::ZCLTypeUInt24:
                case ZCLTypeDataType::ZCLTypeUInt32:
                    info.GetReturnValue().Set(any_cast<uint32_t>(value));
                    break;
                case ZCLTypeDataType::ZCLTypeUInt40:
                case ZCLTypeDataType::ZCLTypeUInt48:
                case ZCLTypeDataType::ZCLTypeUInt56:
                case ZCLTypeDataType::ZCLTypeUInt64:
                    info.GetReturnValue().Set(Integer::New(isolate, any_cast<double>(value)));
                    break;
                case ZCLTypeDataType::ZCLTypeIEEEaddress: {
                    uint64_t ieeeAddress = any_cast<uint64_t>(value);
                    uint64_t bigIeeeAddr = boost::endian::native_to_big(ieeeAddress);
                    ExtAddress extAddress((uint8_t *) &bigIeeeAddr);
                    info.GetReturnValue().Set(String::NewFromUtf8(isolate, extAddress.asString().c_str()));
                    break;
                }
                default:
                    break;
            }
        } catch (std::exception &e) {
            BOOST_LOG_TRIVIAL(error) << "Error reading attribute value: " << e.what();
        }
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
                JSZAttribute *This = getThis(info);

                v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>> persistententObject;
                persistententObject.Reset(isolate, info[0]);
                attribute->requestValue(std::make_unique<JSZAttributeCallback>(persistententObject, &This->callbackFifo, isolate));
            } else {
                v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, "Request method need a callback");
                isolate->ThrowException(errorMsg);
            }

        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
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

    ZCLAttribute *JSZAttribute::getZCLAttribute(const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId, uint32_t attributeId) {
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
        Cluster * cluster = singletonObjects->getClusters()->getCluster(zDevice->getNwkAddr(), endpointId, clusterId);
        ZCLAttribute *attribute = cluster->getAttribute(attributeId);
        if (!attribute) {
            throw JSExceptionNoAttribute(extAddress, endpointId, clusterId, attributeId);
        }
        return attribute;
    }

    JSZAttribute *JSZAttribute::getThis(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
        return (JSZAttribute *) wrap->Value();
    }

    void JSZAttribute::JSZAttributeCallback::response(ZCLAttribute *attribute) {
        auto cluster = attribute->getClusterParent();
        auto nwkAddr = cluster->getNetworkAddress().getId();
        auto endpointId = cluster->getEndpoint().getId();
        auto clusterId = cluster->getId().getId();
        auto attributeId = attribute->getIdentifier();
        auto callback = persistentCallback;

        BOOST_LOG_TRIVIAL(info) << "Arrived attribute " << attributeId << " from " << nwkAddr;

        callbackFifo->add(isolate, [nwkAddr, endpointId, clusterId, attributeId, callback](v8::Isolate *isolate) {
            Local<Value> argv[4];
            argv[0] = v8::Int32::New(isolate, nwkAddr);
            argv[1] = v8::Int32::New(isolate, endpointId);
            argv[2] = v8::Int32::New(isolate, clusterId);
            argv[3] = v8::Int32::New(isolate, attributeId);

            Local<Value> object = Local<Value>::New(isolate, callback);
            Local<Function> callback = Local<Function>::Cast(object);

            callback->CallAsFunction(object, 4, argv);
        });
    }

    void JSZAttribute::JSZAttributeCallback::timeout() {
        BOOST_LOG_TRIVIAL(info) << "Request attribute timeout";
    }

} /* namespace zigbee */
