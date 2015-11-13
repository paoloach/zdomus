/*
 * JSZDevices.cpp
 *
 *  Created on: 27/dic/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <sstream>
#include "JSZDevices.h"
#include "JSObjects.h"

namespace zigbee {

using namespace v8;

JSZDevices::JSZDevices(ZDevices_P  zDevices,JSZDevice_P  jsDevice) :
		zDevices(zDevices), jsDevice(jsDevice) {
}

JSZDevices::~JSZDevices() {
}

void testAccessor(Local<String> , const PropertyCallbackInfo<Value>& ) {

}

void JSZDevices::initJsObjectsTemplate(Isolate * isolate, Handle<ObjectTemplate> & global) {
	Local<String> jszDevicesName = String::NewFromUtf8(isolate, JSZDEVICES);

	Handle<Value> jszDevicesHandle = Handle<Value>::Cast(External::New(isolate, this));
	global->SetAccessor(jszDevicesName, JSZDevices::getZDevices, 0, jszDevicesHandle, ALL_CAN_READ, ReadOnly);
}

void JSZDevices::initJsObjectsIstances(Isolate * isolate, Local<Object> & global) {
	Local<String> getCountDevicesMethods = String::NewFromUtf8(isolate, GETCOUNTDEVICES);
	Local<String> getDevicesMethods = String::NewFromUtf8(isolate, GETDEVICES);
	Local<String> getDeviceMethods = String::NewFromUtf8(isolate, GETDEVICE);

	jsDevice->initJsObjectsTemplate(isolate,global);

	Local<ObjectTemplate> zDevicesTempl = ObjectTemplate::New();
	zDevicesTempl->SetInternalFieldCount(1);
	zDevicesTempl->Set(getCountDevicesMethods, FunctionTemplate::New(isolate, jsGetCountDevices));
	zDevicesTempl->Set(getDevicesMethods, FunctionTemplate::New(isolate, jsGetDevices));
	zDevicesTempl->Set(getDeviceMethods, FunctionTemplate::New(isolate, jsGetDevice));
	Local<Object> zDeviceInstanceLocal = zDevicesTempl->NewInstance();
	zDeviceInstanceLocal->SetInternalField(0, External::New(isolate, this));

	zDevicesInstance.Reset(isolate, zDeviceInstanceLocal);
}

JSZDevices * JSZDevices::getThis(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	return (JSZDevices *) wrap->Value();
}

JSZDevices * JSZDevices::getThis(const v8::PropertyCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
	return (JSZDevices *) wrap->Value();
}

void JSZDevices::getZDevices(Local<String> , const PropertyCallbackInfo<Value>& info) {
	Local<Value> self = info.Data();
	Local<External> wrap = Local<External>::Cast(self);
	void* ptr = wrap->Value();
	JSZDevices * This = (JSZDevices *) (ptr);

	Local<Object> zDeviceInstanceLocal = Local<Object>::New(info.GetIsolate(), This->zDevicesInstance);

	info.GetReturnValue().Set(zDeviceInstanceLocal);
}

void JSZDevices::jsGetCountDevices(const v8::FunctionCallbackInfo<v8::Value>& info) {
	JSZDevices * This = getThis(info);

	info.GetReturnValue().Set(This->zDevices->getNumDevices());
}

void JSZDevices::jsGetDevices(const v8::FunctionCallbackInfo<v8::Value>& info) {
	JSZDevices * This = getThis(info);
	std::vector<ZDevice> devices = This->zDevices->getDevices();

	Local<Array> jsDevices = Array::New(info.GetIsolate(), devices.size());
	for (unsigned int index = 0; index < devices.size(); index++) {
		jsDevices->Set(index, This->jsDevice->createInstance(info.GetIsolate(), devices[index].getExtAddr()));
	}

	info.GetReturnValue().Set(jsDevices);

}

ExtAddress JSZDevices::getExtAddressFromParam(const v8::FunctionCallbackInfo<v8::Value>& params, int index) {
	v8::String::Utf8Value extAddressString(params[index]);
	std::stringstream stream { *extAddressString };
	ExtAddress extAddress { };
	stream >> extAddress;
	return extAddress;
}

void JSZDevices::resetIstances() {
	zDevicesInstance.Reset();
}

void JSZDevices::jsGetDevice(const v8::FunctionCallbackInfo<v8::Value>& info) {
	if (info.Length() != 1) {
		std::stringstream stream { };
		stream << "Invoking ZDevice.getDevice with " << info.Length() << " parameters but expected 1 (the extended address of a valid ZDevice)";
		Local<String> errorMsg = String::NewFromUtf8(info.GetIsolate(), stream.str().c_str());
		info.GetIsolate()->ThrowException(errorMsg);
		return;
	}
	ExtAddress extAddress = getExtAddressFromParam(info, 0);
	JSZDevices * This = getThis(info);
	if (!This->zDevices->exists(extAddress)) {
		std::stringstream stream { };
		stream << "Found any devices with extended address " << extAddress;
		Local<String> errorMsg = String::NewFromUtf8(info.GetIsolate(), stream.str().c_str());
		info.GetIsolate()->ThrowException(errorMsg);
		return;
	}
	info.GetReturnValue().Set(This->jsDevice->createInstance(info.GetIsolate(), extAddress));
}

} /* namespace zigbee */
