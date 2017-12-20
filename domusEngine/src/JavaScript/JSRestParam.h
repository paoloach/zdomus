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
        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, const Pistache::Rest::Request & request);

        virtual void resetPersistences();
    private:
        static void getParam(const v8::FunctionCallbackInfo<v8::Value> &info);
        static void getQuery(const v8::FunctionCallbackInfo<v8::Value> &info);
        static Pistache::Rest::Request * getRequest(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info);
        static void checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index);
    private:
        v8::UniquePersistent<v8::FunctionTemplate> persistentFunctionTemplate;

        static std::string htmlDecode(std::string basic_string);
    };
}


#endif //DOMUS_ENGINE_JSRESTPARAM_H
