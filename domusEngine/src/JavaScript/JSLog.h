/*
 * JSLog.h
 *
 *  Created on: 18/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSLOG_H_
#define SRC_JAVASCRIPT_JSLOG_H_

#include <v8.h>
#include <memory>

#include "../Utils/Log.h"

namespace zigbee {

class JSLog {
public:
	JSLog(Log & log);
	virtual ~JSLog();
public:
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global);
	virtual v8::Local<v8::Object> createInstance(v8::Isolate* isolate);
	virtual void resetPersistences();
protected:
	static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void debug(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void info(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void warning(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void error(const v8::FunctionCallbackInfo<v8::Value>& info);
	static Log * getLog(const v8::FunctionCallbackInfo<v8::Value>& info);
	static std::string getMessage(const v8::FunctionCallbackInfo<v8::Value>& info);
private:
	v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;

	Log & log;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSLOG_H_ */