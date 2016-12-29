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
#include "../Utils/SingletonObjects.h"
#include "JavaScriptExecuter.h"

namespace zigbee {

    using namespace v8;
    using std::make_unique;
    using namespace boost::posix_time;

    JavaScriptExecuter::JavaScriptExecuter(SingletonObjects &singletonObjects, time_duration period, Log &log) : period(period), log(log), jsLog(log),
                                                                                                                 jsZCluster(&jsZAttributeFactory, &singletonObjects),
                                                                                                                 jsDBTable(dbTableFactory, &jsRow, log),
                                                                                                                 jsZEndpoint(singletonObjects.getZDevices(), &jsZCluster),
                                                                                                                 jsZEndpoints(singletonObjects, &jsZEndpoint),
                                                                                                                 jsZDevice(singletonObjects.getZDevices(), &jsZEndpoint),
                                                                                                                 jsRestServer(singletonObjects.getFixedPathContainer(), log),
                                                                                                                 jszDevices(singletonObjects.getZDevices(), &jsZDevice),
                                                                                                                 stop(false) {

        createParams.array_buffer_allocator = &v8Allocator;
        isolate = v8::Isolate::New(createParams);

        jsZAttributeFactory.init(&singletonObjects, callbackFifo);
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
        jsRow.initJsObjectsTemplate(isolate, contextGlobal);
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
        jsDBTable.resetPersistences();
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
        while (!stop) {
            ptime nextTime(second_clock::local_time()+period);
            TryCatch tryCatch;
            MaybeLocal<Value> result = script->Run(lContext);
            if (tryCatch.HasCaught()) {
                String::Utf8Value utf8Message(tryCatch.Message()->Get());
                log.error(*utf8Message);
                tryCatch.Reset();
            } else {
                //String::Utf8Value utf8(result);
            }
            while (nextTime > second_clock::local_time() && !stop) {
                while (callbackFifo.size(isolate) > 0) {
                    auto fn = callbackFifo.get(isolate);
                    fn(isolate);
                }
                sleep(1);
            }

        }

        Unlocker unlocker(isolate);
        BOOST_LOG_TRIVIAL(info) << "End script";
        notifyEnd();
    }

    void JavaScriptExecuter::join() {
        stop = true;
        jsThread.join();
    }

    void JavaScriptExecuter::run(const std::string &jsCode) {
        this->jsCode = jsCode;
        jsThread = std::thread([this]{runThread();});
    }

    boost::signals2::connection JavaScriptExecuter::notificationEnd(const OnEnd &onEnd) {
        return notifyEnd.connect(onEnd);
    }

} /* namespace zigbee */
