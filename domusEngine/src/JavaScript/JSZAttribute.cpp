/*
 * JSZAttribute.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
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

namespace zigbee {

using namespace v8;
using std::stringstream;

std::map<ZCLAttribute::Status, std::string> JSZAttribute::statusMap = { { ZCLAttribute::Available, "available" }, { ZCLAttribute::NotAvailable, "notAvailable" }, {
		ZCLAttribute::NotSupported, "notSupported" }, { ZCLAttribute::Requesting, "requesting" }, { ZCLAttribute::Undefined, "undefined" }, };

JSZAttribute::JSZAttribute(const std::shared_ptr<ZDevices>& zDevices, const std::shared_ptr<ZigbeeDevice> & zigbeeDevice,
		const std::shared_ptr<ClusterTypeFactory> & clusterFactory) :
		zDevices(zDevices), zigbeeDevice(zigbeeDevice), clusterFactory(clusterFactory) {
}

JSZAttribute::~JSZAttribute() {
	for (auto & function: mapFunction){
		std::get<0>(function.second).disconnect();
		std::get<1>(function.second).Reset();
	}

}

void JSZAttribute::initJsObjectsTemplate(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& zAttributeFunctionTemplate) {
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

void JSZAttribute::validateParams(const v8::FunctionCallbackInfo<v8::Value>& info) {
	if (info.Length() != 4) {
		throw JSException("Invalid params: expected 4 (extended address, endpoint id, cluster id, attribute id)");
	}
}

v8::Local<v8::Object> JSZAttribute::createInstance(v8::Isolate* isolate, const std::shared_ptr<ZCLAttribute>& zclAttribute) {
	if (zclAttribute->getZCLType() != getZCLDataType()) {
		throw JSExceptionInvalidAttributeType(getName(), zclAttribute->getZCLType(), getZCLDataType());
	}
	Local<ObjectTemplate> zAttributeT = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
	Local<Object> zAttributeInstance = zAttributeT->NewInstance();

	zAttributeInstance->SetInternalField(0, External::New(isolate, zclAttribute.get()));
	zAttributeInstance->SetInternalField(1, External::New(isolate, this));
	return zAttributeInstance;
}

void JSZAttribute::constructor(const v8::FunctionCallbackInfo<v8::Value>& info) {
	if (info.IsConstructCall()) {
		return;
	}
	Isolate * isolate = info.GetIsolate();
	try {
		validateParams(info);
		ExtAddress extAddress = getExtAddressFromArg(info);
		EndpointID endpointId( info[1].As<v8::Integer>()->Value());
		ClusterID clusterId (info[2].As<v8::Integer>()->Value());
		uint32_t attributeId =  info[3].As<v8::Integer>()->Value();
		JSZAttribute * This = (JSZAttribute *) (Local<External>::Cast(info.Data())->Value());

		std::shared_ptr<ZCLAttribute> zclAttribute = This->getZCLAttribute(extAddress, endpointId, clusterId, attributeId);

		info.GetReturnValue().Set(This->createInstance(isolate, zclAttribute));
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

ExtAddress JSZAttribute::getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value>& info) {
	v8::String::Utf8Value extAddressString(info[0]);
	std::stringstream stream { *extAddressString };
	ExtAddress extAddress { };
	stream >> extAddress;
	return extAddress;
}

void JSZAttribute::jsRequestValue(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<Object> self = info.Holder();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		if (info.Length() == 1) {
			if (!info[0]->IsFunction()) {
				throw JSExceptionArgNoFunction(0);
			}
			Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
			JSZAttribute * This = (JSZAttribute *) wrap->Value();

			v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>> persistenteObject;
			persistenteObject.Reset(isolate, info[0]);

			Local<Function> callback = Local<Function>::Cast(info[0]);
			int identity = callback->GetIdentityHash();
			boost::signals2::connection con = attribute->onChange(std::bind(&JSZAttribute::signalChange, This, isolate, identity));
			std::lock_guard<std::mutex> lock(This->mapFunctionMutex);
			This->mapFunction.insert( { identity, std::make_tuple(con, persistenteObject) });
		}
		attribute->requestValue();
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::signalChange(v8::Isolate * isolate, int identity) {
	if (mapFunction.count(identity) > 0) {
		CallbackData callbackData  = popCallbackData(identity);
		Local<Value> object = Local<Value>::New(isolate, std::get<1>(callbackData));
		Local<Function> callback = Local<Function>::Cast(object);
		String::Utf8Value name(callback->GetInferredName());

		callback->CallAsFunction(object, 0, nullptr);
		std::get<0>(callbackData).disconnect();
		std::get<1>(callbackData).Reset();
	}
}

void JSZAttribute::jsIsAvailable(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		info.GetReturnValue().Set(attribute->isAvailable());
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::jsIsUnsupported(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		info.GetReturnValue().Set(attribute->isUnsupported());
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::jsGetStatus(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		ZCLAttribute::Status status = attribute->getStatus();
		Local<String> name = String::NewFromUtf8(isolate, statusMap[status].c_str());
		info.GetReturnValue().Set(name);
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::jsGetIdentifier(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		info.GetReturnValue().Set(attribute->getIdentifier());
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::jsGetName(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		Local<String> name = String::NewFromUtf8(isolate, attribute->getName().c_str());
		info.GetReturnValue().Set(name);
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::jsIsReadOnly(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	try {
		Local<External> wrap = Local<External>::Cast(info.Holder()->GetInternalField(0));
		ZCLAttribute * attribute = (ZCLAttribute *) wrap->Value();
		info.GetReturnValue().Set(attribute->isReadOnly());
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

void JSZAttribute::resetPersistence() {
	functionTemplate.Reset();
}

std::shared_ptr<ZCLAttribute> JSZAttribute::getZCLAttribute(const ExtAddress& extAddress, EndpointID endpointId, ClusterID clusterId, uint32_t attributeId) {
	if (!zDevices->exists(extAddress)) {
		throw JSExceptionNoDevice(extAddress);
	}
	const ZDevice & zDevice = zDevices->getDevice(extAddress);
	if (!zDevice.isEndpointPresents(endpointId)) {
		throw JSExceptionNoEndpoint(extAddress, endpointId);
	}
	ZEndpoint zEndpoint = zDevice.getEndpoint(endpointId);
	if (!zEndpoint.hasInCluster(clusterId)) {
		throw JSExceptionNoInCluster(extAddress, endpointId, clusterId);
	}
	std::shared_ptr<Cluster> cluster = clusterFactory->getCluster(clusterId, zigbeeDevice, endpointId, zDevice.getNwkAddr());
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