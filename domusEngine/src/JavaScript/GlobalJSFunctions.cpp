//
// Created by paolo on 29/12/16.
//
#include <unistd.h>
#include "GlobalJSFunctions.h"
#include "JSObjects.h"
#include "Exceptions/JSException.h"
#include "Exceptions/JSExceptionOnlyOneArgument.h"
#include "Exceptions/JSExceptionArgNoInteger.h"

using namespace v8;

namespace zigbee {

    void GlobalJSFunctions::initFunctions(Isolate *isolate, Handle<Object> &) {
        Local<String> fnNameWait = String::NewFromUtf8(isolate, JSWAIT);

        Local<FunctionTemplate> zEndpoinFunctionTemplate = FunctionTemplate::New(isolate, fnWait);
        zEndpoinFunctionTemplate->SetClassName(fnNameWait);
    }

    void GlobalJSFunctions::fnWait(const v8::FunctionCallbackInfo<v8::Value> &info) {
        auto isolate = info.GetIsolate();
        try {
            if (info.kArgsLength != 1) {
                throw JSExceptionOnlyOneArgument(JSWAIT);
            }
            Local<Value> arg0 = info[0];
            if (!arg0->IsInt32()) {
                throw JSExceptionArgNoInteger(std::string(JSWAIT), 0);
            }
            auto toWait = arg0->Int32Value();
            usleep(toWait*1000);

        }catch (JSException &jsException) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
            isolate->ThrowException(errorMsg);
        }
    }

}
