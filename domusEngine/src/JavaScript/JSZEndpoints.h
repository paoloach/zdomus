//
// Created by paolo on 27/12/16.
//

#ifndef DOMUS_ENGINE_JSZENDPOINTS_H
#define DOMUS_ENGINE_JSZENDPOINTS_H

#include <v8.h>
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class JSZEndpoint;

    class JSZEndpoints {
    public:
        JSZEndpoints(SingletonObjects &singletonObjects, JSZEndpoint *jszEndpoint) : singletonObjects(singletonObjects),
                                                                                     jszEndpoint(jszEndpoint) {

        }

        virtual ~JSZEndpoints() = default;

    public:
        void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::ObjectTemplate> &global);

        void initJsObjectsInstance(v8::Isolate *isolate);

        void resetInstance();

    private:
        static JSZEndpoints *getThis(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void getZEndpoints(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info);

        static void getEndpointsWithCluster(const v8::FunctionCallbackInfo<v8::Value> &info);

    private:
        v8::UniquePersistent<v8::Object> zEndpointsInstance;
        SingletonObjects &singletonObjects;
        JSZEndpoint *jszEndpoint;
    };

} /* namespace zigbee */


#endif //DOMUS_ENGINE_JSZENDPOINTS_H
