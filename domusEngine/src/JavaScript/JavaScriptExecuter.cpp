/*
 * JavaScriptExecuter.cpp
 *
 *  Created on: 26/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <iostream>
#include <v8.h>

#include <zcl/Cluster.h>
#include "JavaScriptExecuter.h"
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace zigbee {

    using namespace v8;
    using std::make_unique;
    using namespace boost::posix_time;

    JavaScriptExecuter::JavaScriptExecuter(SingletonObjects *singletonObjects, std::chrono::seconds period) : period(period), jsResultSet(&jsRow),
                                                                                                              jsDBTable(dbTableFactory, &jsRow, &jsResultSet),
                                                                                                              jsZCluster(&jsZAttributeFactory, singletonObjects),
                                                                                                              jsZEndpoint(singletonObjects->getZDevices(), &jsZCluster),
                                                                                                              jsZEndpoints(singletonObjects, &jsZEndpoint),
                                                                                                              jsZDevice(singletonObjects->getZDevices(), &jsZEndpoint),
                                                                                                              jsRestServer(singletonObjects->getRestHandler(), &callbackFifo,
                                                                                                                           &jsRestParam),
                                                                                                              jszDevices(singletonObjects->getZDevices(), &jsZDevice), stop(false) {

        createParams.array_buffer_allocator = &v8Allocator;
        isolate = v8::Isolate::New(createParams);

        jsZAttributeFactory.init(singletonObjects, callbackFifo);
        Isolate::Scope isolate_scope(isolate);
        Locker locker(isolate);
        HandleScope handle_scope(isolate);

        Handle<ObjectTemplate> global = ObjectTemplate::New();

        jszDevices.initJsObjectsTemplate(isolate, global);
        jsZEndpoints.initJsObjectsTemplate(isolate, global);

        Local<Context> lContext = Context::New(isolate, nullptr, global);
        Context::Scope context_scope(lContext);
        Local<Object> contextGlobal = lContext->Global();
        jszDevices.initJsObjectsIstances(isolate, contextGlobal);
        jsZEndpoint.initJsObjectsTemplate(isolate, contextGlobal);
        jsZEndpoints.initJsObjectsInstance(isolate);
        jsZCluster.initJsObjectsTemplate(isolate, contextGlobal);
        jsZAttributeFactory.initJsObjectsTemplate(isolate, contextGlobal);
        jsLog.initJsObjectsTemplate(isolate, contextGlobal);
        jsRestServer.initJsObjectsTemplate(isolate, contextGlobal);
        jsRestParam.initJsObjectsTemplate(isolate, contextGlobal);
        jsRow.initJsObjectsTemplate(isolate, contextGlobal);
        jsResultSet.initJsObjectsTemplate(isolate, contextGlobal);
        jsDBTable.initJsObjectsTemplate(isolate, contextGlobal);
        globalJSFunctions.initFunctions(isolate, contextGlobal);

        context.Reset(isolate, lContext);
    }

    JavaScriptExecuter::~JavaScriptExecuter() {
        jszDevices.resetIstances();
        jsZEndpoints.resetInstance();
        jsZCluster.resetPersistences();
        jsZEndpoint.resetPersistences();
        jsZAttributeFactory.resetPersistences();
        jsZDevice.resetPersistences();
        jsLog.resetPersistences();
        jsRestServer.resetPersistences();
        jsRow.resetPersistences();
        jsResultSet.resetPersistences();
        jsDBTable.resetPersistences();
        jsRestParam.resetPersistences();
        context.Reset();
        isolate->Dispose();
        jszDevices.resetIstances();
    }

    void JavaScriptExecuter::runThread() {
        Isolate::Scope isolate_scope(isolate);
        Locker locker(isolate);

        HandleScope handle_scope(isolate);

        Local<Context> lContext = Local<Context>::New(isolate, context);
        Context::Scope contextScope(lContext);
        Local<String> source = String::NewFromUtf8(isolate, jsCode.c_str());
        Local<Script> script = Script::Compile(source);
        auto nextTime = std::chrono::system_clock::now() + period;
        while (!stop) {
            TryCatch tryCatch;
            auto result = script->Run(lContext);
            if (tryCatch.HasCaught()) {
                String::Utf8Value utf8Message(tryCatch.Message()->Get());
                tryCatch.Reset();
            }

            auto wait = std::chrono::duration_cast<std::chrono::seconds>(nextTime - std::chrono::system_clock::now());
            callbackFifo.execute(isolate, wait);
            nextTime = nextTime + period;
        }

        Unlocker unlocker(isolate);
        notifyEnd();
    }

    void JavaScriptExecuter::join() {
        stop = true;
        jsThread.join();
    }

    void JavaScriptExecuter::run(const std::string &jsCode) {
        this->jsCode = jsCode;
        stop=false;
        jsThread = std::thread([this] { runThread(); });
    }

    boost::signals2::connection JavaScriptExecuter::notificationEnd(const OnEnd &onEnd) {
        return notifyEnd.connect(onEnd);
    }

} /* namespace zigbee */
