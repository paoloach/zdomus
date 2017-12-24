/*
 * JSDBTable.cpp
 *
 *  Created on: 19/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSDBTable.h"
#include "JSObjects.h"
#include <boost/log/trivial.hpp>

#include "../Database/DBTableFactory.h"
#include "../Database/DBTable.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "Exceptions/JSExceptionOnlyOneArgument.h"
#include "JSRow.h"
#include "JSResultSet.h"

namespace zigbee {

    using std::stringstream;
    using std::string;
    using namespace v8;
    using std::any;

    JSDBTable::JSDBTable(DBTableFactory &dbTableFactory, JSRow *jsRow, JSResultSet *resultSet) : dbTableFactory(dbTableFactory), jsRow(jsRow), jsResult(resultSet) {

    }

    void JSDBTable::initJsObjectsTemplate(v8::Isolate *isolate, Handle<Object> &global) {
        Local<String> jsDbTableClassName = String::NewFromUtf8(isolate, JSDBTABLE);
        // methods
        Local<String> findMethod = String::NewFromUtf8(isolate, FIND);
        Local<String> insertMethod = String::NewFromUtf8(isolate, INSERT);

        Local<FunctionTemplate> logFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        logFunctionTemplate->SetClassName(jsDbTableClassName);
        Local<ObjectTemplate> dbTableInstanceTemplate = logFunctionTemplate->InstanceTemplate();

        dbTableInstanceTemplate->SetInternalFieldCount(2);
        // functions
        dbTableInstanceTemplate->Set(insertMethod, FunctionTemplate::New(isolate, insert));
        dbTableInstanceTemplate->Set(findMethod, FunctionTemplate::New(isolate, find));
        global->Set(jsDbTableClassName, logFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, logFunctionTemplate);
    }

    Local<Object> JSDBTable::createInstance(Isolate *isolate, const string &tableName) {
        Local<ObjectTemplate> dbTableTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> dbTableInstance = dbTableTemplate->NewInstance();

        DBTable *dbTable = dbTableFactory.getTable(tableName);

        dbTableInstance->SetInternalField(0, External::New(isolate, dbTable));
        dbTableInstance->SetInternalField(1, External::New(isolate, this));

        return dbTableInstance;
    }

    void JSDBTable::resetPersistences() {
        functionTemplate.Reset();
    }

    void JSDBTable::checkConstructorParams(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 1) {
            throw JSExceptionArgNoString(JSDBTABLE, 0);
        }
        if (!info[0]->IsString()) {
            throw JSExceptionArgNoString(JSDBTABLE, 0);
        }
    }

    void JSDBTable::constructor(const FunctionCallbackInfo<Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        JSDBTable *This = nullptr;

        try {
            This = (JSDBTable *) (Local<External>::Cast(info.Data())->Value());
            checkConstructorParams(info);
            String::Utf8Value tableName(info[0]);
            info.GetReturnValue().Set(This->createInstance(isolate, *tableName));
        } catch (std::exception &excp) {
            if (This != nullptr) {
                BOOST_LOG_TRIVIAL(error) << excp.what();
            }
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSDBTable::find(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        JSDBTable *This = nullptr;
        try {
            This = getJSDbTable(info);
            checkSingleParam(FIND, info);
            checkStringParam(FIND, info, 0);
            String::Utf8Value fieldName(info[0]);

            DBTable *dbTable = getDbTable(info);
            info.GetReturnValue().Set(This->jsResult->createInstance(isolate, dbTable->find(*fieldName)));
        } catch (std::exception &excp) {
            if (This != nullptr) {
                BOOST_LOG_TRIVIAL(error) << excp.what();
            }
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSDBTable::checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 1) {
            throw JSExceptionOnlyOneArgument(methodName);
        }
    }

    DBTable *JSDBTable::getDbTable(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        DBTable *dbTable = (DBTable *) wrap->Value();
        if (dbTable == nullptr) {
            throw JSException("Internal error: invalid instance of dbTable");
        }
        return dbTable;
    }

    JSDBTable *JSDBTable::getJSDbTable(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
        JSDBTable *dbJSTable = (JSDBTable *) wrap->Value();
        if (dbJSTable == nullptr) {
            throw JSException("Internal error: invalid instance of dbTable");
        }
        return dbJSTable;
    }

    void JSDBTable::insert(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        JSDBTable *This = nullptr;
        try {
            This = getJSDbTable(info);
            checkSingleParam(INSERT, info);
            DBTable *dbTable = getDbTable(info);
            Local<Object> jsRow = info[0]->ToObject();
            Local<External> externalRow = jsRow->GetInternalField(0).As<External>();
            DBRow *row = (DBRow *) externalRow->Value();
            dbTable->insert(row);
        } catch (std::exception &excp) {
            if (This != nullptr) {
                BOOST_LOG_TRIVIAL(error) << excp.what();
            }
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSDBTable::checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index) {
        if (!info[0]->IsString()) {
            throw JSExceptionArgNoString(methodName, index);
        }
    }

} /* namespace zigbee */
