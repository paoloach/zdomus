/*
 * JSLog.cpp
 *
 *  Created on: 18/gen/2015
 *      Author: Paolo Achdjian
 */


#include <boost/log/trivial.hpp>
#include "JSLog.h"

#include "JSObjects.h"

namespace zigbee {

    using std::stringstream;
    using namespace v8;

    void JSLog::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> jszLogClassName = String::NewFromUtf8(isolate, JSLOG);
        // methods
        Local<String> debugMethod = String::NewFromUtf8(isolate, DEBUG);
        Local<String> infoMethod = String::NewFromUtf8(isolate, INFO);
        Local<String> warnMethod = String::NewFromUtf8(isolate, WARN);
        Local<String> errorMethod = String::NewFromUtf8(isolate, ERROR);

        Local<FunctionTemplate> logFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        logFunctionTemplate->SetClassName(jszLogClassName);
        Local<ObjectTemplate> logInstanceTemplate = logFunctionTemplate->InstanceTemplate();

        logInstanceTemplate->Set(debugMethod, FunctionTemplate::New(isolate, debug));
        logInstanceTemplate->Set(infoMethod, FunctionTemplate::New(isolate, info));
        logInstanceTemplate->Set(warnMethod, FunctionTemplate::New(isolate, warning));
        logInstanceTemplate->Set(errorMethod, FunctionTemplate::New(isolate, error));
        global->Set(jszLogClassName, logFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, logFunctionTemplate);
    }

    v8::Local<v8::Object> JSLog::createInstance(v8::Isolate *isolate) {

        Local<ObjectTemplate> logTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> logInstance = logTemplate->NewInstance();

        return logInstance;
    }

    void JSLog::resetPersistences() {
        functionTemplate.Reset();
    }

    void JSLog::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            JSLog *This = (JSLog *) (Local<External>::Cast(info.Data())->Value());
            info.GetReturnValue().Set(This->createInstance(info.GetIsolate()));
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSLog::debug(const v8::FunctionCallbackInfo<v8::Value> &info) {
        std::string msg = getMessage(info);
        BOOST_LOG_TRIVIAL(debug) << msg;
    }

    void JSLog::info(const v8::FunctionCallbackInfo<v8::Value> &info) {
        std::string msg = getMessage(info);
        BOOST_LOG_TRIVIAL(info) << msg;
    }

    void JSLog::warning(const v8::FunctionCallbackInfo<v8::Value> &info) {
        std::string msg = getMessage(info);
        BOOST_LOG_TRIVIAL(warning) << msg;
    }

    void JSLog::error(const v8::FunctionCallbackInfo<v8::Value> &info) {
        std::string msg = getMessage(info);
    }

    std::string JSLog::getMessage(const v8::FunctionCallbackInfo<v8::Value> &info) {
        std::stringstream stream;
        int length = info.Length();
        for (int i = 0; i < length; i++) {
            String::Utf8Value utf8Value(info[i]);
            stream << *utf8Value;
            if (i < (length - 1)) {
                stream << ", ";
            }
        }
        return stream.str();
    }

} /* namespace zigbee */
