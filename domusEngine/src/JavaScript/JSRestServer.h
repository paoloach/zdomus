/*
 * JSRestServer.h
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSRESTSERVER_H_
#define SRC_JAVASCRIPT_JSRESTSERVER_H_

#include <v8.h>
#include <memory>
#include "../httpServer/FixedPathContainer.h"

namespace zigbee {

class Log;

class JSRestServer {
public:
	JSRestServer(std::shared_ptr<http::FixedPathContainer> fixedPathContainer, Log & log);
	virtual ~JSRestServer();
public:
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global);
	virtual v8::Local<v8::Object> createInstance(v8::Isolate* isolate);
	virtual void resetPersistences();
protected:
	static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void addPathMethod(const v8::FunctionCallbackInfo<v8::Value>& info);
	static Log*   getLog(const v8::FunctionCallbackInfo<v8::Value>& info);
	static http::FixedPathContainer*   getContainer(const v8::FunctionCallbackInfo<v8::Value>& info);
private:
	static void checkStringParam(const std::string& methodName, const v8::FunctionCallbackInfo<v8::Value>& info, uint32_t index);
private:
	std::shared_ptr<http::FixedPathContainer> fixedPathContainer;
	Log & log;
	v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSRESTSERVER_H_ */
