/*
 * JSRestServer.h
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSRESTSERVER_H_
#define SRC_JAVASCRIPT_JSRESTSERVER_H_

#include <v8.h>
#include <memory>
#include <map>
#include <condition_variable>
#include <mutex>
#include "JSCallbackFifo.h"
#include "../httpServer/ExternalRestPath.h"

namespace zigbee {

    class Log;

    class JSRestServer {
    public:
        JSRestServer(http::ExternalRestPath * fixedPathContainer, Log &log, JSCallbackFifo * jsCallbackFifo): fixedPathContainer(fixedPathContainer), log(log), jsCallbackFifo(jsCallbackFifo) {}

        virtual ~JSRestServer()=default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate);

        virtual void resetPersistences();

    protected:
        static void constructor(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void addPathMethod(const v8::FunctionCallbackInfo<v8::Value> &info);
                void addPathMethodInternal(const v8::FunctionCallbackInfo<v8::Value> &info);

        static JSRestServer * getThis(const v8::FunctionCallbackInfo<v8::Value> &info);

    private:
        static void checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index);
        std::string callback(v8::Isolate *isolate, int functionId,http::ExternalRestPath::CallbackArgs & args);
        void asyncCallback(v8::Isolate *, int functionId, http::ExternalRestPath::CallbackArgs args);

    private:
        http::ExternalRestPath * fixedPathContainer;
        Log &log;
        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
        JSCallbackFifo * jsCallbackFifo;
        std::map<int, v8::Persistent<v8::Value, v8::CopyablePersistentTraits<v8::Value>>> callbackMap;
        std::map<int, std::string> results;
        std::map<int, std::unique_ptr<std::condition_variable>> conditionVariables;
        std::mutex mutex;

    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSRESTSERVER_H_ */
