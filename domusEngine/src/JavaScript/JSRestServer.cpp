/*
 * JSRestServer.cpp
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#include "JSRestServer.h"
#include "JSObjects.h"
#include "Exceptions/JSExceptionOnlyTwoArguments.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "../Exception/Timeout.h"
#include "../httpServer/RestHandler.h"

namespace zigbee {

    using std::stringstream;
    using namespace std::chrono_literals;
    using namespace v8;
    using Net::Rest::Route;
    using Net::Rest::Request;
    using Net::Http::ResponseWriter;
    using Net::Http::Code;

    void JSRestServer::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> jsClassName = String::NewFromUtf8(isolate, JSRESTSERVER);

        // methods
        Local<String> addPathMethodName = String::NewFromUtf8(isolate, ADD_PATH);

        Local<FunctionTemplate> restServerFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        restServerFunctionTemplate->SetClassName(jsClassName);
        Local<ObjectTemplate> restServerLogInstanceTemplate = restServerFunctionTemplate->InstanceTemplate();

        restServerLogInstanceTemplate->SetInternalFieldCount(1);
        // functions
        restServerLogInstanceTemplate->Set(addPathMethodName, FunctionTemplate::New(isolate, addPathMethod));
        global->Set(jsClassName, restServerFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, restServerFunctionTemplate);

    }

    v8::Local<v8::Object> JSRestServer::createInstance(v8::Isolate *isolate) {
        Local<ObjectTemplate> restServerTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> restServerInstance = restServerTemplate->NewInstance();

        restServerInstance->SetInternalField(0, External::New(isolate, this));

        return restServerInstance;
    }

    void JSRestServer::resetPersistences() {
        functionTemplate.Reset();
    }

    void JSRestServer::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            JSRestServer *This = (JSRestServer *) (Local<External>::Cast(info.Data())->Value());
            info.GetReturnValue().Set(This->createInstance(info.GetIsolate()));
        } catch (std::exception &excp) {
            BOOST_LOG_TRIVIAL(error) << excp.what();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    JSRestServer *JSRestServer::getThis(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        JSRestServer *This = (JSRestServer *) wrap->Value();
        if (This == nullptr) {
            BOOST_LOG_TRIVIAL(error) << "Internal error: invalid instance of JSRestServer";
            throw JSException("Internal error: invalid instance of JSRestServer");
        }
        return This;
    }

    void JSRestServer::addPathMethod(const v8::FunctionCallbackInfo<v8::Value> &info) {
        try {
            JSRestServer *This = getThis(info);
            This->addPathMethodInternal(info);
        } catch (JSException &jsException) {
            BOOST_LOG_TRIVIAL(error) << jsException.what();
            Isolate *isolate = info.GetIsolate();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSRestServer::addPathMethodInternal(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            if (info.Length() != 2) {
                throw JSExceptionOnlyTwoArguments(ADD_PATH);
            }
            checkStringParam(ADD_PATH, info, 0);
            String::Utf8Value path(info[0]);
            Route::Handler fn;
            std::string a = *path;
            auto arg = info[1];
            if (arg->IsFunction()) {
                Local<Function> callback = Local<Function>::Cast(arg);
                int functionId = callback->GetIdentityHash();
                callbackMap[functionId].Reset(isolate, arg);
                fn = [this, functionId, isolate](const Request& request, ResponseWriter response)->Route::Result {
                    return this->callback(isolate, functionId, request, std::move(response) );
                };
            } else {
                String::Utf8Value valueUtf8(arg->ToString());
                std::string value = *valueUtf8;
                fn = [value](const Request& request, ResponseWriter response ) ->Route::Result{
                    response.send(Code::Ok, value);
                    return Route::Result::Ok;
                };
            }
            restHandler->addGetPath(*path, fn);
        } catch (JSException &jsException) {
            BOOST_LOG_TRIVIAL(error) << jsException.what();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSRestServer::asyncCallback(Isolate * isolate, int functionId,const Net::Rest::Request& request) {
        if (callbackMap.count(functionId) > 0){
            Local<Value> object = Local<Value>::New(isolate, callbackMap[functionId]);
            Local<Function> callback = Local<Function>::Cast(object);
            if (!callback.IsEmpty()) {
                String::Utf8Value name(callback->GetInferredName());

                auto context = callback->CreationContext();
                auto jsPlaceHolders = jsRestParam->createInstance(isolate, request);
                Local<Value> jsArgs[1] = {jsPlaceHolders};

                TryCatch tryCatch;

                MaybeLocal<Value> result = callback->CallAsFunction(context, object, 1, jsArgs);
                if (tryCatch.HasCaught()){
                    BOOST_LOG_TRIVIAL(error) << "javascipt function " << *name << " return an exception: " << *String::Utf8Value( tryCatch.Message()->Get());
                }
                if (!result.IsEmpty()){
                    String::Utf8Value valueUtf8(result.ToLocalChecked()->ToString());
                    results[functionId] = *valueUtf8;
                }
                if (conditionVariables[functionId]  > 0){
                    conditionVariables[functionId]->notify_all();
                }
            }
        }
    }


    void JSRestServer::checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index) {
        if (!info[0]->IsString()) {
            throw JSExceptionArgNoString(methodName, index);
        }
    }

    Net::Rest::Route::Result JSRestServer::callback(v8::Isolate *isolate, int functionId, const Net::Rest::Request &request, Net::Http::ResponseWriter && response) {
        if (conditionVariables.count(functionId) ==0){
            conditionVariables[functionId] = std::make_unique<std::condition_variable>();
        }
        jsCallbackFifo->add(isolate, [this, functionId, request, isolate](Isolate * ){asyncCallback(isolate, functionId, request);});
        BOOST_LOG_TRIVIAL(info) << "Waiting result ";
        std::unique_lock<std::mutex> lock(mutex);
        auto status = conditionVariables[functionId]->wait_for(lock, 60s);
        if (status == std::cv_status::timeout){
            response.send(Code::Internal_Server_Error, "Timeout");
            throw Timeout("timeout (60secondi) calling javascript callback");
        } else {
            response.send(Code::Ok, results[functionId]);
        }
        return Route::Result::Ok;
    }

} /* namespace zigbee */
