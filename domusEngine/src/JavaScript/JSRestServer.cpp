/*
 * JSRestServer.cpp
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#include "JSRestServer.h"
#include "JSObjects.h"
#include "Exceptions/JSExceptionOnlyTwoArguments.h"
#include "Exceptions/JSException.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "../Utils/Log.h"

namespace zigbee {

using std::stringstream;
using namespace v8;

JSRestServer::JSRestServer(std::shared_ptr<http::FixedPathContainer> fixedPathContainer, Log & log) :
		fixedPathContainer(fixedPathContainer), log(log) {
}

JSRestServer::~JSRestServer() {
}

void JSRestServer::initJsObjectsTemplate(v8::Isolate* isolate, v8::Handle<v8::Object>& global) {
	Local<String> jsClassName = String::NewFromUtf8(isolate, JSRESTSERVER);

	// methods
	Local<String> addPathMethodName = String::NewFromUtf8(isolate, ADD_PATH);

	Local<FunctionTemplate> restServerFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
	restServerFunctionTemplate->SetClassName(jsClassName);
	Local<ObjectTemplate> restServerLogInstanceTemplate = restServerFunctionTemplate->InstanceTemplate();

	restServerLogInstanceTemplate->SetInternalFieldCount(2);
	// functions
	restServerLogInstanceTemplate->Set(addPathMethodName, FunctionTemplate::New(isolate, addPathMethod));
	global->Set(jsClassName, restServerFunctionTemplate->GetFunction());

	functionTemplate.Reset(isolate, restServerFunctionTemplate);

}

v8::Local<v8::Object> JSRestServer::createInstance(v8::Isolate* isolate) {
	Local<ObjectTemplate> restServerTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
	Local<Object> restServerInstance = restServerTemplate->NewInstance();

	restServerInstance->SetInternalField(0, External::New(isolate, &fixedPathContainer));
	restServerInstance->SetInternalField(1, External::New(isolate, &log));

	return restServerInstance;
}

void JSRestServer::resetPersistences() {
	functionTemplate.Reset();
}

void JSRestServer::constructor(const v8::FunctionCallbackInfo<v8::Value>& info) {
	if (info.IsConstructCall()) {
		return;
	}
	Isolate * isolate = info.GetIsolate();
	try {
		JSRestServer * This = (JSRestServer *) (Local<External>::Cast(info.Data())->Value());
		info.GetReturnValue().Set(This->createInstance(info.GetIsolate()));
	} catch (std::exception & excp) {
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
		isolate->ThrowException(errorMsg);
	}
}

Log* JSRestServer::getLog(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
	Log * log = (Log *) wrap->Value();
	if (log == nullptr) {
		throw JSException("Internal error: invalid instance of log");
	}
	return log;
}

void JSRestServer::addPathMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Isolate * isolate = info.GetIsolate();
	Log * log = nullptr;
	try {
		log = getLog(info);
		http::FixedPathContainer * container = getContainer(info);
		if (info.Length() != 2) {
			throw JSExceptionOnlyTwoArguments(ADD_PATH);
		}
		checkStringParam(ADD_PATH, info, 0);
		String::Utf8Value path(info[0]);
		String::Utf8Value value(info[1]->ToString());
		container->addRestValue({*path, *value});
	} catch (JSException & jsException) {
		if (log != nullptr) {
			log->error(jsException.what());
		}
		v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
		isolate->ThrowException(errorMsg);
	}
}

http::FixedPathContainer* JSRestServer::getContainer(const v8::FunctionCallbackInfo<v8::Value>& info) {
	Local<Object> self = info.Holder();
	Local<External> wrap = Local<External>::Cast(self->GetInternalField(2));
	http::FixedPathContainer * container = (http::FixedPathContainer *) wrap->Value();
	if (container == nullptr) {
		throw JSException("Internal error: invalid instance of FixedPathContainer");
	}
	return container;
}

void JSRestServer::checkStringParam(const std::string& methodName, const v8::FunctionCallbackInfo<v8::Value>& info, uint32_t index) {
	if (!info[0]->IsString()) {
		throw JSExceptionArgNoString(methodName, index);
	}
}

} /* namespace zigbee */
