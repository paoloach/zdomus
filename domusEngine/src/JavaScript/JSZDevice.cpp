/*
 * JSZDevice.cpp
 *
 *  Created on: 28/dic/2014
 *      Author: Paolo Achdjian
 */

#include "JSZDevice.h"
#include "JSObjects.h"

#include <sstream>
#include "../ZigbeeData/ZDevice.h"
#include "JSZEndpoint.h"

namespace zigbee {

using namespace v8;

JSZDevice::JSZDevice(ZDevices_P  zDevices,JSZEndpoint_P & jsEndpoint) :
		zDevices(zDevices) , jsEndpoint(jsEndpoint){
}

JSZDevice::~JSZDevice() {
	for (auto jszDeviceObj : cache) {
		jszDeviceObj.second.Reset();
	}
}

void JSZDevice::initJsObjectsTemplate(v8::Isolate* isolate, Handle<Object> & global) {
	Local<String> jszDeviceName = String::NewFromUtf8(isolate, JSZDEVICE);
	// attributes
	Local<String> getLongAddressMethods = String::NewFromUtf8(isolate, GETLONGADDRESS);
	Local<String> getShortAddressMethods = String::NewFromUtf8(isolate, GETSHORTADDRESS);
	// methods
	Local<String> isPanMethod = String::NewFromUtf8(isolate, IS_PAN);
	Local<String> isFullFunctionDeviceMethod = String::NewFromUtf8(isolate, IS_FFD);
	Local<String> isMainPoweredSourceMethod = String::NewFromUtf8(isolate, IS_POWEREDSOURCE);
	Local<String> isDisableRFInIdleMethod = String::NewFromUtf8(isolate, IS_DISABLE_RF_IDLE);
	Local<String> isSecureCapableMethod = String::NewFromUtf8(isolate, IS_SECURE_CAPABILITY);
	Local<String> getEndpoints = String::NewFromUtf8(isolate, GETENDPOINTS);

	Local<FunctionTemplate> zDeviceFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
	zDeviceFunctionTemplate->SetClassName(jszDeviceName);
	Local<ObjectTemplate> zDevicesTempl = zDeviceFunctionTemplate->InstanceTemplate();

	zDevicesTempl->SetInternalFieldCount(3);
	// attributes
	zDevicesTempl->SetAccessor(getLongAddressMethods, jsGetLongAddress);
	zDevicesTempl->SetAccessor(getShortAddressMethods, jsGetShortAddress);
	// functions
	zDevicesTempl->Set(isPanMethod, FunctionTemplate::New(isolate, jsIsPan));
	zDevicesTempl->Set(isFullFunctionDeviceMethod, FunctionTemplate::New(isolate, jsIsFullFunctionDevice));
	zDevicesTempl->Set(isMainPoweredSourceMethod, FunctionTemplate::New(isolate, jsIsMainPoweredSource));
	zDevicesTempl->Set(isDisableRFInIdleMethod, FunctionTemplate::New(isolate, jsIsDisableRFInIdle));
	zDevicesTempl->Set(isSecureCapableMethod, FunctionTemplate::New(isolate, jsIsSecureCapable));
	zDevicesTempl->Set(getEndpoints, FunctionTemplate::New(isolate, jsGetEndpoints));
	// constructor
	global->Set(jszDeviceName, zDeviceFunctionTemplate->GetFunction());

	functionTemplate.Reset(isolate, zDeviceFunctionTemplate);
}

Local<Object> JSZDevice::createInstance(v8::Isolate* isolate, const ExtAddress& extAddress) {
	if (cache.count(extAddress) == 0) {
		if (!zDevices->exists(extAddress)) {
			std::stringstream stream { };
			stream << "Unable to create an istance of zDevice with extended address " << extAddress;
			Local<String> errorMsg = String::NewFromUtf8(isolate, stream.str().c_str());
			isolate->ThrowException(errorMsg);
			return Local<Object>();
		}

		Local<ObjectTemplate> zDeviceTempl = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
		Local<Object> zDeviceInstance = zDeviceTempl->NewInstance();
		std::shared_ptr<ExtAddress> usedAddr { };
		if (usedExtAddresses.count(extAddress) == 0) {
			usedAddr = std::make_shared<ExtAddress>(extAddress);
			usedExtAddresses[extAddress] = usedAddr;
		} else {
			usedAddr = usedExtAddresses[extAddress];
		}
		zDeviceInstance->SetInternalField(0, External::New(isolate, usedAddr.get()));
		zDeviceInstance->SetInternalField(1, External::New(isolate, zDevices.get()));
		zDeviceInstance->SetInternalField(2, External::New(isolate, jsEndpoint.get()));
		Persistent<Object, CopyablePersistentTraits<Object>> persitInstance { isolate, zDeviceInstance };
		cache.insert( { extAddress, persitInstance });
		return zDeviceInstance;
	} else {
		return Local<Object>::New(isolate, cache[extAddress]);
	}
}

ExtAddress * JSZDevice::getExtAddress(const v8::PropertyCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	return (ExtAddress *) wrap->Value();
}

ZDevices * JSZDevice::getZDevices(const v8::PropertyCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
	return (ZDevices *) wrap->Value();
}

ExtAddress * JSZDevice::getExtAddress(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	return (ExtAddress *) wrap->Value();
}

void JSZDevice::constructor(const v8::FunctionCallbackInfo<v8::Value>& info) {
	JSZDevice * This = (JSZDevice *) (Local<External>::Cast(info.Data())->Value());

	if (info.Length() != 1) {
		return;
	}
	v8::String::Utf8Value extAddressString(info[0]);
	std::stringstream stream { *extAddressString };
	ExtAddress extAddress { };
	stream >> extAddress;
	info.GetReturnValue().Set(This->createInstance(info.GetIsolate(), extAddress));
}

void JSZDevice::jsIsFullFunctionDevice(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	info.GetReturnValue().Set(zDevice.isFullFunctionDevice());
}

void JSZDevice::jsIsMainPoweredSource(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	info.GetReturnValue().Set(zDevice.isMainPower());
}

void JSZDevice::jsIsDisableRFInIdle(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	info.GetReturnValue().Set(zDevice.isDisabledRFOnIdle());
}

void JSZDevice::jsIsSecureCapable(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	info.GetReturnValue().Set(zDevice.isSecure());
}

void JSZDevice::jsGetEndpoints(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	JSZEndpoint * jsEndpoint = getJSEndpoint(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	const std::map<EndpointID, ZEndpoint> & endpoints = zDevice.getEndpoints();
	Local<Array> jsEndpoints = Array::New(info.GetIsolate(), endpoints.size());
	int index { 0 };
	for (const auto & endpoint : endpoints) {
		v8::Local<Object> zEndpoint =  jsEndpoint->createInstance(info.GetIsolate(), *extAddress, endpoint.second.getEndpoint());
		jsEndpoints->Set(index, zEndpoint);
		index++;
	}
	info.GetReturnValue().Set(jsEndpoints);
}

ZDevices * JSZDevice::getZDevices(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
	return (ZDevices *) wrap->Value();
}

void JSZDevice::jsIsPan(const v8::FunctionCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);
	info.GetReturnValue().Set(zDevice.isPan());
}

void JSZDevice::jsGetLongAddress(v8::Local<v8::String> , const v8::PropertyCallbackInfo<v8::Value>& info) {
	std::stringstream stream { };
	ExtAddress * extAddress = getExtAddress(info);
	stream << (*extAddress);
	info.GetReturnValue().Set(String::NewFromUtf8(info.GetIsolate(), stream.str().c_str()));
}

void JSZDevice::jsGetShortAddress(v8::Local<v8::String> , const v8::PropertyCallbackInfo<v8::Value>& info) {
	ExtAddress * extAddress = getExtAddress(info);
	ZDevices * zDevices = getZDevices(info);
	const ZDevice & zDevice = zDevices->getDevice(*extAddress);

	info.GetReturnValue().Set(zDevice.getNwkAddr().getId());
}


JSZEndpoint* JSZDevice::getJSEndpoint(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(2));
	return (JSZEndpoint *) wrap->Value();
}
void JSZDevice::resetPersistences() {
	functionTemplate.Reset();
}

} /* namespace zigbee */

