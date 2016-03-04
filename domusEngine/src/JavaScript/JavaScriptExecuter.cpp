/*
 * JavaScriptExecuter.cpp
 *
 *  Created on: 26/dic/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <functional>
#include <v8.h>

#include "../Utils/SingletonObjects.h"
#include "JavaScriptExecuter.h"

namespace zigbee {

using namespace v8;


JavaScriptExecuter::JavaScriptExecuter(SingletonObjects & singletonObjects, Log & log):singletonObjects(singletonObjects), log(log){

	clusterTypeFactory = std::make_shared<ClusterTypeFactory>();
	jsRow = std::make_shared<JSRow>();
	jsDBTable = std::make_shared<JSDBTable>(dbTableFactory, jsRow, log);
	jsZEndpoint = std::make_shared<JSZEndpoint>(singletonObjects.getZDevices());
	jsZDevice = std::make_shared<JSZDevice>(singletonObjects.getZDevices(),jsZEndpoint);
	jsLog = std::make_shared<JSLog>(log);
	jsRestServer = std::make_shared<JSRestServer>(singletonObjects.getFixedPathContainer(),log);
	jszDevices = std::make_shared<JSZDevices>(singletonObjects.getZDevices(),jsZDevice);
	jsZAttributeFactory = std::make_shared<JSZAttributeFactory>();
	jsZCluster = std::make_shared<JSZCluster>(singletonObjects.getZDevices(), singletonObjects.getZigbeeDevice(),jsZAttributeFactory,clusterTypeFactory);
	createParams.array_buffer_allocator = &v8Allocator;
    isolate = v8::Isolate::New(createParams);

	jsZAttributeFactory->init(singletonObjects.getZDevices(), singletonObjects.getZigbeeDevice(), clusterTypeFactory);
	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	jszDevices->initJsObjectsTemplate(isolate,global);

	Local<Context> lContext = Context::New(isolate,nullptr,global);
	Context::Scope context_scope(lContext);
	Local<Object> contextGlobal = lContext->Global();
	jszDevices->initJsObjectsIstances(isolate,contextGlobal);
	jsZEndpoint->initJsObjectsTemplate(isolate, contextGlobal);
	jsZCluster->initJsObjectsTemplate(isolate, contextGlobal);
	jsZAttributeFactory->initJsObjectsTemplate(isolate, contextGlobal);
	jsLog->initJsObjectsTemplate(isolate, contextGlobal);
	jsRestServer->initJsObjectsTemplate(isolate, contextGlobal);
	jsRow->initJsObjectsTemplate(isolate, contextGlobal);
	jsDBTable->initJsObjectsTemplate(isolate, contextGlobal);
	context.Reset(isolate, lContext);


}

JavaScriptExecuter::~JavaScriptExecuter() {
	jszDevices->resetIstances();
	jsZCluster->resetPersistences();
	jsZEndpoint->resetPersistences();
	jsZAttributeFactory->resetPersistences();
	jsZDevice->resetPersistences();
	jsLog->resetPersistences();
	jsRestServer->resetPersistences();
	jsRow->resetPersistences();
	jsDBTable->resetPersistences();
	context.Reset();
	isolate->Dispose();
	jszDevices.reset();
}

void JavaScriptExecuter::runThread() {


	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);

	HandleScope handle_scope(isolate);

	Local<Context> lContext = Local<Context>::New(isolate,context);
	Context::Scope contextScope(lContext);

	Local<String> source = String::NewFromUtf8(isolate, jsCode.c_str()	);
	Local<Script> script = Script::Compile(source);
	TryCatch tryCatch;
	Local<Value> result = script->Run();
	if (tryCatch.HasCaught()){
		String::Utf8Value utf8Message(tryCatch.Message()->Get());
		log.error( *utf8Message);
		tryCatch.Reset();
	} else {
		String::Utf8Value utf8(result);
	}
	Unlocker unlocker(isolate);
	notifyEnd();
}

void JavaScriptExecuter::join() {
	jsThread.join();
}

void JavaScriptExecuter::run(const std::string & jsCode) {
	this->jsCode = jsCode;
	jsThread = std::thread(std::bind(&JavaScriptExecuter::runThread, this));
}
boost::signals2::connection JavaScriptExecuter::notificationEnd(const OnEnd & onEnd) {
	return notifyEnd.connect(onEnd);
}

} /* namespace zigbee */
