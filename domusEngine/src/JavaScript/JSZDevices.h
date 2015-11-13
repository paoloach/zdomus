/*
 * JSZDevices.h
 *
 *  Created on: 27/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZDEVICES_H_
#define SRC_JAVASCRIPT_JSZDEVICES_H_

#include <v8.h>
#include "../ZigbeeData/ZDevices.h"
#include "JSZDevice.h"

namespace zigbee {

class JSZDevices {
public:
	JSZDevices(ZDevices_P   zDevices,JSZDevice_P  jsDevice);
	virtual ~JSZDevices();
public:
	void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::ObjectTemplate> & global );
	void initJsObjectsIstances(v8::Isolate * isolate, v8::Local<v8::Object> & global );
	void resetIstances();
private:
	static JSZDevices * getThis(const v8::FunctionCallbackInfo<v8::Value>& info);
	static JSZDevices * getThis(const v8::PropertyCallbackInfo<v8::Value>& info);
	static ExtAddress getExtAddressFromParam(const v8::FunctionCallbackInfo<v8::Value>& params, int index);
	static void getZDevices( v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void jsGetCountDevices(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void jsGetDevices(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void jsGetDevice(const v8::FunctionCallbackInfo<v8::Value>& info);
private:
	v8::UniquePersistent<v8::Object> zDevicesInstance;
	ZDevices_P  zDevices;
	JSZDevice_P jsDevice;
};

typedef std::shared_ptr<JSZDevices> JSZDevices_P;

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZDEVICES_H_ */
