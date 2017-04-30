//
// Created by paolo on 29/04/17.
//

#ifndef DOMUS_ENGINE_JSRESTPARAM_H
#define DOMUS_ENGINE_JSRESTPARAM_H

#include <v8.h>
#include "router.h"

namespace zigbee {
    class JSRestParam {
    public:
        virtual ~JSRestParam() = default;
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);
        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, const Net::Rest::Request & request);

        virtual void resetPersistences();
    private:
        static void getParam(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info);
        static void checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index);
    private:
        v8::UniquePersistent<v8::FunctionTemplate> persistentFunctionTemplate;
    };
}


#endif //DOMUS_ENGINE_JSRESTPARAM_H
