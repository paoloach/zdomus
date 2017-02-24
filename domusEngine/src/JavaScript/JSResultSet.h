//
// Created by paolo on 21/02/17.
//

#ifndef DOMUS_ENGINE_JSRESULTSET_H
#define DOMUS_ENGINE_JSRESULTSET_H

#include <v8.h>
#include <libpq-fe.h>


namespace zigbee {
    class JSRow;
    class DBRow;

    class JSResultSet {
    public:
        JSResultSet(JSRow *jsRow):jsRow(jsRow){}
        virtual ~JSResultSet() = default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, PGresult *resultSet);

        virtual void resetPersistences();

    protected:
        static void nextRow(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void previousRow(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void weakCallback(const v8::WeakCallbackInfo<PGresult> &data);

        static std::unique_ptr<DBRow> makeDBRow(PGresult *resultSet, uint currentIndex);

    private:
        static JSRow *getJsRow(const v8::FunctionCallbackInfo<v8::Value> &info);
        static PGresult *getPGResult(const v8::FunctionCallbackInfo<v8::Value> &info);

        v8::UniquePersistent<v8::FunctionTemplate> persistentFunctionTemplate;
        JSRow * jsRow;
    };
}


#endif //DOMUS_ENGINE_JSRESULTSET_H
