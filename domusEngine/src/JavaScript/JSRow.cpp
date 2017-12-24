/*
 * JSRow.cpp
 *
 *  Created on: 22/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include "JSRow.h"
#include "JSObjects.h"
#include "Exceptions/JSExceptionArgNoString.h"
#include "Exceptions/JSExceptionOnlyTwoArguments.h"
#include "Exceptions/JSExceptionOnlyOneArgument.h"

#include "V8anyConverter.h"

namespace zigbee {

    using std::stringstream;
    using std::string;
    using namespace v8;
    using std::any;

    void JSRow::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> jsDbRowClassName = String::NewFromUtf8(isolate, JSDBROW);
        // methods
        Local<String> getValueMethod = String::NewFromUtf8(isolate, GET_VALUE);
        Local<String> setValueMethod = String::NewFromUtf8(isolate, SET_VALUE);

        Local<FunctionTemplate> logFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        logFunctionTemplate->SetClassName(jsDbRowClassName);
        Local<ObjectTemplate> dbRowInstanceTemplate = logFunctionTemplate->InstanceTemplate();

        dbRowInstanceTemplate->SetInternalFieldCount(2);
        // functions
        dbRowInstanceTemplate->Set(getValueMethod, FunctionTemplate::New(isolate, getValue));
        dbRowInstanceTemplate->Set(setValueMethod, FunctionTemplate::New(isolate, setValue));
        global->Set(jsDbRowClassName, logFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, logFunctionTemplate);
    }

    v8::Local<v8::Object> JSRow::createInstance(v8::Isolate *isolate, std::unique_ptr<DBRow> &&  dbRow) {
        if (createdObject.count(dbRow.get())) {
            Local<Object> object = Local<Object>::New(isolate, createdObject[dbRow.get()]);
            return object;
        }
        Local<ObjectTemplate> dbRowTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> dbRowInstance = dbRowTemplate->NewInstance();
        Persistent<v8::Object> newObject;

        dbRowInstance->SetInternalField(0, External::New(isolate, dbRow.get()));
        dbRow.release();
        dbRowInstance->SetInternalField(1, External::New(isolate, this));

        newObject.Reset(isolate, dbRowTemplate->NewInstance());
        newObject.SetWeak(this, weakCallback, WeakCallbackType::kParameter);
        v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>> persistObject;
        persistObject.Reset(isolate, newObject);
        createdObject[dbRow.get()].Reset(isolate, newObject);

        return dbRowInstance;
    }

    void JSRow::resetPersistences() {
        functionTemplate.Reset();
        createdObject.clear();
    }

    void zigbee::JSRow::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            JSRow *This = (JSRow *) (Local<External>::Cast(info.Data())->Value());

            info.GetReturnValue().Set(This->createInstance(isolate, std::make_unique<DBRow>()));
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSRow::getValue(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            checkSingleParam(GET_VALUE, info);
            checkStringParam(GET_VALUE, info, 0);
            String::Utf8Value fieldName(info[0]);

            DBRow *dbRow = getDbRow(info);

            Local<Value> data = V8_any_Converter::convertToV8(isolate, dbRow->getValue(*fieldName));
            info.GetReturnValue().Set(data);
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void zigbee::JSRow::setValue(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            checkTwoParam(SET_VALUE, info);
            checkStringParam(SET_VALUE, info, 0);
            String::Utf8Value fieldName(info[0]);
            any value = V8_any_Converter::convertToAny(info[1]);

            DBRow *dbRow = getDbRow(info);
            dbRow->setValue(*fieldName, value);
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    DBRow *JSRow::getDbRow(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        DBRow *dbTable = (DBRow *) wrap->Value();
        if (dbTable == nullptr) {
            throw JSException("Internal error: invalid instance of dbTable");
        }
        return dbTable;
    }

    void JSRow::checkSingleParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 1) {
            throw JSExceptionOnlyOneArgument(methodName);
        }
    }

    void JSRow::checkStringParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info, uint32_t index) {
        if (!info[0]->IsString()) {
            throw JSExceptionArgNoString(methodName, index);
        }
    }

    void JSRow::checkTwoParam(const std::string &methodName, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 2) {
            throw JSExceptionOnlyTwoArguments(methodName);
        }
    }

    void JSRow::weakCallback(const v8::WeakCallbackInfo<JSRow> &data) {

        BOOST_LOG_TRIVIAL(info) << "Called weakCallback" << std::endl;
        JSRow *This = data.GetParameter();

        DBRow *  dbRow = (DBRow *) data.GetInternalField(0);

        This->createdObject.erase(dbRow);
        delete dbRow;
    }

} /* namespace zigbee */

