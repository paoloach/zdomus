//
// Created by paolo on 21/02/17.
//

#include <boost/log/trivial.hpp>
#include "JSObjects.h"
#include "JSResultSet.h"
#include "JSRow.h"
#include "Exceptions/JSException.h"
#include "../Database/DBRow.h"
#include "../Database/DBDataConverter.h"

namespace zigbee {
    using v8::String;
    using v8::Local;
    using v8::FunctionTemplate;
    using v8::ObjectTemplate;
    using v8::External;
    using v8::Isolate;
    using v8::Handle;
    using v8::Object;
    using v8::Persistent;
    using v8::NonCopyablePersistentTraits;
    using v8::WeakCallbackType;
    using std::string;

    void JSResultSet::initJsObjectsTemplate(Isolate *isolate, Handle<Object> &global) {
        Local<String> className = String::NewFromUtf8(isolate, JSRESULT_SET);
        // methods
        Local<String> nextRowMethod = String::NewFromUtf8(isolate, NEXTROW);
        Local<String> previousRowMethod = String::NewFromUtf8(isolate, PREVIOUSROW);

        Local<FunctionTemplate> functionTemplate = FunctionTemplate::New(isolate);
        functionTemplate->SetClassName(className);
        Local<ObjectTemplate> dbTableInstanceTemplate = functionTemplate->InstanceTemplate();

        dbTableInstanceTemplate->SetInternalFieldCount(4);
        // functions
        dbTableInstanceTemplate->Set(nextRowMethod, FunctionTemplate::New(isolate, nextRow));
        dbTableInstanceTemplate->Set(previousRowMethod, FunctionTemplate::New(isolate, previousRow));
        global->Set(className, functionTemplate->GetFunction());

        persistentFunctionTemplate.Reset(isolate, functionTemplate);
    }

    Local<Object> JSResultSet::createInstance(Isolate *isolate, PGresult *resultSet) {
        Local<ObjectTemplate> jsTemplate = Local<FunctionTemplate>::New(isolate, persistentFunctionTemplate)->InstanceTemplate();
        Local<Object> newInstance = jsTemplate->NewInstance();
        Persistent<Object, NonCopyablePersistentTraits<Object>> newObject;

        newInstance->SetInternalField(0, External::New(isolate, jsRow));
        newInstance->SetInternalField(1, External::New(isolate, resultSet));
        newInstance->SetInternalField(2, v8::Int32::New(isolate, 0));
        newInstance->SetInternalField(3, v8::Int32::New(isolate, PQntuples(resultSet)));
        newObject.Reset(isolate, newInstance);
        newObject.SetWeak(resultSet, weakCallback, WeakCallbackType::kParameter);

        return newInstance;
    }

    void JSResultSet::resetPersistences() {
        persistentFunctionTemplate.Reset();
    }


    void JSResultSet::weakCallback(const v8::WeakCallbackInfo<PGresult> &data) {

        BOOST_LOG_TRIVIAL(info) << "Called JSResultSet::weakCallback" << std::endl;
        PGresult *resultSet = data.GetParameter();

        PQclear(resultSet);
    }

    JSRow *JSResultSet::getJsRow(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        JSRow *jsRow = static_cast<JSRow *>( wrap->Value());
        if (jsRow == nullptr) {
            throw JSException("Internal error: invalid instance of JSResultSet");
        }
        return jsRow;
    }

    PGresult *JSResultSet::getPGResult(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
        PGresult *result = static_cast<PGresult *>( wrap->Value());
        if (result == nullptr) {
            throw JSException("Internal error: invalid instance of JSResultSet");
        }
        return result;
    }

    void JSResultSet::nextRow(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            int currentIndex = info.Holder()->GetInternalField(2)->Int32Value();
            int maxResult = info.Holder()->GetInternalField(3)->Int32Value();
            if (currentIndex < maxResult ) {
                currentIndex++;
                info.Holder()->SetInternalField(2, v8::Int32::New(isolate, currentIndex));
                auto result = getPGResult(info);
                auto jsRow = getJsRow(info);

                info.GetReturnValue().Set(jsRow->createInstance(isolate, makeDBRow(result, currentIndex-1)));
            }
        } catch (std::exception &excp) {
            BOOST_LOG_TRIVIAL(error) << excp.what();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSResultSet::previousRow(const v8::FunctionCallbackInfo<v8::Value> &info){
        Isolate *isolate = info.GetIsolate();
        try {
            int currentIndex = info.Holder()->GetInternalField(2)->Int32Value();
            if (currentIndex > 0) {
                currentIndex--;
                info.Holder()->SetInternalField(2, v8::Int32::New(isolate, currentIndex));
                auto result = getPGResult(info);
                auto jsRow = getJsRow(info);

                info.GetReturnValue().Set(jsRow->createInstance(isolate, makeDBRow(result, currentIndex)));
            }
        } catch (std::exception &excp) {
            BOOST_LOG_TRIVIAL(error) << excp.what();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    std::unique_ptr<DBRow> JSResultSet::makeDBRow(PGresult *resultSet, uint currentIndex) {
        auto dbRow = std::make_unique<DBRow>();

        int fieldCount = PQnfields(resultSet);

        for (int colIndex = 0; colIndex < fieldCount; colIndex++) {
            std::string fieldName = PQfname(resultSet, colIndex);
            if (PQgetisnull(resultSet, currentIndex, colIndex) == 0) {
                DBDataConverter::DBData dbData(resultSet, currentIndex, colIndex);
                boost::any value = DBDataConverter::getAnyValue(dbData);
                dbRow->setValue(fieldName, value);
            } else {
                dbRow->setValue(fieldName, boost::any());
            }
        }

        return dbRow;
    }
}
