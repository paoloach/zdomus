/*
 * JSDBTable.h
 *
 *  Created on: 19/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSDBTABLE_H_
#define SRC_JAVASCRIPT_JSDBTABLE_H_

#include <v8.h>
#include <memory>
#include <boost/any.hpp>

namespace zigbee {

    class DBTableFactory;

    class DBTable;

    class JSRow;
    class JSResultSet;

    class JSDBTable {
    public:
        JSDBTable(DBTableFactory &dbTableFactory, JSRow *jsRow, JSResultSet * resultSet);

        virtual ~JSDBTable() = default;

    public:
        virtual void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

        virtual v8::Local<v8::Object> createInstance(v8::Isolate *isolate, const std::string &tableName);

        virtual void resetPersistences();

    protected:
        static void checkConstructorParams(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void constructor(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void find(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void insert(const v8::FunctionCallbackInfo<v8::Value> &info);


        static DBTable *getDbTable(const v8::FunctionCallbackInfo<v8::Value> &info);

        static JSDBTable *getJSDbTable(const v8::FunctionCallbackInfo<v8::Value> &info);

        static void checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info);


        static void checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index);


    private:
        DBTableFactory &dbTableFactory;
        JSRow *jsRow;
        JSResultSet * jsResult;
        v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSDBTABLE_H_ */
