//
// Created by paolo on 17/11/17.
//

#ifndef DOMUS_ENGINE_JSBASE_H
#define DOMUS_ENGINE_JSBASE_H

#include <v8.h>

namespace zigbee {
    class JSBase {
    protected:
        static void setClassName(const char * name, v8::Isolate * isolate, v8::Handle<v8::Object> &global, v8::Local<v8::FunctionTemplate> functionTemplate){
            auto className = v8::String::NewFromUtf8(isolate, name);
            functionTemplate->SetClassName(className);
            global->Set(className, functionTemplate->GetFunction());
        }

        static void addMethod(const char * name ,v8::Isolate *isolate, v8::Local<v8::ObjectTemplate> & objTemplate,  v8::FunctionCallback func ){
            auto methodName = v8::String::NewFromUtf8(isolate, name);
            objTemplate->Set(methodName, v8::FunctionTemplate::New(isolate, func));
        }
    };
}


#endif //DOMUS_ENGINE_JSBASE_H
