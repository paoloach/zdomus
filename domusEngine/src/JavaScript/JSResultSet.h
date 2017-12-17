//
// Created by paolo on 21/02/17.
//

#ifndef DOMUS_ENGINE_JSRESULTSET_H
#define DOMUS_ENGINE_JSRESULTSET_H

#include <libpq-fe.h>
#include "JSBase.h"
#include "../Database/ResultSet.h"


namespace zigbee {
    class JSRow;
    class DBRow;

    class JSResultSet : public JSBase {
    public:
        JSResultSet(JSRow *jsRow):jsRow(jsRow){}
        virtual ~JSResultSet() = default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, ResultSet && resultSet);

        virtual void resetPersistences();

    protected:
        static void nextRow(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void previousRow(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void stringify(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void weakCallback(const v8::WeakCallbackInfo<ResultSet> &data);

        static std::unique_ptr<DBRow> makeDBRow(ResultSet *resultSet, uint currentIndex);

    private:
        static constexpr int FIELD_ACTUAL_ROW=0;
        static constexpr int FIELD_RESULT_SET=1;
        static constexpr int FIELD_CURRENT_INDEX=2;
        static constexpr int FIELD_MAX_INDEX=3;
        static JSRow *getJsRow(const v8::FunctionCallbackInfo<v8::Value> &info);
        static ResultSet *getPGResult(const v8::FunctionCallbackInfo<v8::Value> &info);

        v8::UniquePersistent<v8::FunctionTemplate> persistentFunctionTemplate;
        JSRow * jsRow;
    };
}


#endif //DOMUS_ENGINE_JSRESULTSET_H
