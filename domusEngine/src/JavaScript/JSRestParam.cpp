//
// Created by paolo on 29/04/17.
//

#include <boost/log/trivial.hpp>
#include "JSRestParam.h"
#include "JSObjects.h"
#include "Exceptions/JSExceptionOnlyOneArgument.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "V8anyConverter.h"

using std::stringstream;
using std::string;
using namespace v8;
using Net::Rest::Request;

namespace zigbee {

    void JSRestParam::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> className = String::NewFromUtf8(isolate, JSRESTPARAM);
        // methods
        Local<String> getParamMethod = String::NewFromUtf8(isolate, GET_PARAM);
        Local<String> getQueryMethod = String::NewFromUtf8(isolate, GET_QUERY);

        Local<FunctionTemplate> functionTemplate = FunctionTemplate::New(isolate, 0, External::New(isolate, this));
        functionTemplate->SetClassName(className);
        Local<ObjectTemplate> instanceTemplate = functionTemplate->InstanceTemplate();

        instanceTemplate->SetInternalFieldCount(1);
        // functions
        instanceTemplate->Set(getParamMethod, FunctionTemplate::New(isolate, getParam));
        instanceTemplate->Set(getQueryMethod, FunctionTemplate::New(isolate, getQuery));
        global->Set(className, functionTemplate->GetFunction());

        persistentFunctionTemplate.Reset(isolate, functionTemplate);
    }

    v8::Local<v8::Object> JSRestParam::createInstance(v8::Isolate *isolate, const Request &request) {
        Local<ObjectTemplate> objectTemplate = Local<FunctionTemplate>::New(isolate, persistentFunctionTemplate)->InstanceTemplate();
        Local<Object> object = objectTemplate->NewInstance();
        Persistent<v8::Object> newObject;

        object->SetInternalField(0, External::New(isolate, const_cast<Net::Rest::Request *>(&request)));

        return object;
    }

    void JSRestParam::getParam(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            String::Utf8Value paramName(info[0]);
            auto  request = getRequest(info);

            auto value = request->param(*paramName).as<string>();

            info.GetReturnValue().Set(String::NewFromUtf8(isolate, value.c_str()));
        } catch (std::exception &exception) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, exception.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSRestParam::getQuery(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            String::Utf8Value paramName(info[0]);
            auto  request = getRequest(info);

            auto value = request->query().get(*paramName);

            if (!value.isEmpty()){
                std::string decoded = htmlDecode(value.get());
                info.GetReturnValue().Set(String::NewFromUtf8(isolate, decoded.c_str()));
            }

        } catch (std::exception &exception) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, exception.what());
            isolate->ThrowException(errorMsg);
        }
    }

    Request * JSRestParam::getRequest(const v8::FunctionCallbackInfo<v8::Value> &info){
        checkSingleParam(GET_PARAM, info);
        checkStringParam(GET_PARAM, info, 0);

        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));

        Request * request = (Request *) wrap->Value();
        if (request == nullptr) {
            throw JSException("Internal error: invalid instance of dbTable");
        }
        return request;
    }

    void JSRestParam::checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 1) {
            throw JSExceptionOnlyOneArgument(methodName);
        }
    }

    void JSRestParam::checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index) {
        if (!info[0]->IsString()) {
            throw JSExceptionArgNoString(methodName, index);
        }
    }

    void JSRestParam::resetPersistences() {
        persistentFunctionTemplate.Reset();
    }

    std::string JSRestParam::htmlDecode(std::string value) {
        std::string result;
        auto iter = std::begin(value);
        auto end = std::end(value);
        while (iter != end){
            if (*iter != '%'){
                result += *iter;

            } else {
                iter++;
                int d1 = *iter-'0';
                iter++;
                int d2 = *iter-'0';
                int decoded = d1*16+d2;
                result += (char)decoded;
            }
            iter++;
        }
        return result;
    }
}