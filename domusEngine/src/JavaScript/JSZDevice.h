/*
 * JSZDevice.h
 *
 *  Created on: 28/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZDEVICE_H_
#define SRC_JAVASCRIPT_JSZDEVICE_H_

#include <v8.h>
#include <memory>
#include <map>
#include <set>

#include "../ZigbeeData/ZDevices.h"

namespace zigbee {

class JSZEndpoint;

class JSZDevice {
public:
	JSZDevice(){};
	JSZDevice(ZDevices_P  zDevices, std::shared_ptr<JSZEndpoint> & jsEndpoint);
	virtual ~JSZDevice();
public:
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global );
	virtual v8::Local<v8::Object> createInstance(v8::Isolate* isolate, const ExtAddress & extAddress);
	virtual void resetPersistences();
private:
	void static constructor(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsGetLongAddress(v8::Local<v8::String> property,const v8::PropertyCallbackInfo<v8::Value>& info);
	void static jsGetShortAddress(v8::Local<v8::String> property,const v8::PropertyCallbackInfo<v8::Value>& info);
	void static jsIsPan(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsIsFullFunctionDevice(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsIsMainPoweredSource(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsIsDisableRFInIdle(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsIsSecureCapable(const v8::FunctionCallbackInfo<v8::Value>& info);
	void static jsGetEndpoints(const v8::FunctionCallbackInfo<v8::Value>& info);
	static ExtAddress * getExtAddress(const v8::PropertyCallbackInfo<v8::Value>& info);
	static ZDevices * getZDevices(const v8::PropertyCallbackInfo<v8::Value>& info);
	static ExtAddress * getExtAddress(const v8::FunctionCallbackInfo<v8::Value>& info);
	static ZDevices * getZDevices(const v8::FunctionCallbackInfo<v8::Value>& info);
	static JSZEndpoint * getJSEndpoint(const v8::FunctionCallbackInfo<v8::Value>& info);
private:
	ZDevices_P  zDevices;
	std::shared_ptr<JSZEndpoint> jsEndpoint;

	v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
	std::map<ExtAddress, std::shared_ptr<ExtAddress> > usedExtAddresses;
	std::map<ExtAddress, v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object> > > cache;
};

typedef std::shared_ptr<JSZDevice> JSZDevice_P;


} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZDEVICE_H_ */
