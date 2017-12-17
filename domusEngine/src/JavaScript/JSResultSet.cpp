//
// Created by paolo on 21/02/17.
//

#include <boost/log/trivial.hpp>
#include "JSObjects.h"
#include "JSResultSet.h"
#include "JSRow.h"
#include "Exceptions/JSException.h"
#include "../Database/DBDataConverter.h"
#include "../json/json/json.h"

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
    using namespace Json;
    using std::string;

    void JSResultSet::initJsObjectsTemplate(Isolate *isolate, Handle<Object> &global) {
        Local<FunctionTemplate> functionTemplate = FunctionTemplate::New(isolate);
        Local<ObjectTemplate> dbTableInstanceTemplate = functionTemplate->InstanceTemplate();
        dbTableInstanceTemplate->SetInternalFieldCount(4);
        setClassName(JSRESULT_SET, isolate, global, functionTemplate);
        addMethod(NEXTROW, isolate,dbTableInstanceTemplate,  nextRow);
        addMethod(PREVIOUSROW, isolate,dbTableInstanceTemplate,  previousRow);
        addMethod(STRINGIFY, isolate,dbTableInstanceTemplate,  stringify);

        persistentFunctionTemplate.Reset(isolate, functionTemplate);
    }


    Local<Object> JSResultSet::createInstance(Isolate *isolate, ResultSet && resultSet) {
        Local<ObjectTemplate> jsTemplate = Local<FunctionTemplate>::New(isolate, persistentFunctionTemplate)->InstanceTemplate();
        Local<Object> newInstance = jsTemplate->NewInstance();
        Persistent<Object, NonCopyablePersistentTraits<Object>> newObject;
        ResultSet * p = new ResultSet(resultSet);

        newInstance->SetInternalField(FIELD_ACTUAL_ROW, External::New(isolate, jsRow));
        newInstance->SetInternalField(FIELD_RESULT_SET, External::New(isolate, p));
        newInstance->SetInternalField(FIELD_CURRENT_INDEX, v8::Int32::New(isolate, 0));
        newInstance->SetInternalField(FIELD_MAX_INDEX, v8::Int32::New(isolate, resultSet.numberOfRow()));
        newObject.Reset(isolate, newInstance);
        newObject.SetWeak(p, weakCallback, WeakCallbackType::kParameter);

        return newInstance;
    }

    void JSResultSet::resetPersistences() {
        persistentFunctionTemplate.Reset();
    }


    void JSResultSet::weakCallback(const v8::WeakCallbackInfo<ResultSet> &data) {

        BOOST_LOG_TRIVIAL(info) << "Called JSResultSet::weakCallback" << std::endl;
        ResultSet *resultSet = data.GetParameter();
        delete resultSet;
    }

    JSRow *JSResultSet::getJsRow(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(FIELD_ACTUAL_ROW));
        JSRow *jsRow = static_cast<JSRow *>( wrap->Value());
        if (jsRow == nullptr) {
            throw JSException("Internal error: invalid instance of JSResultSet");
        }
        return jsRow;
    }

    ResultSet *JSResultSet::getPGResult(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(FIELD_RESULT_SET));
        ResultSet *result = static_cast<ResultSet *>( wrap->Value());
        if (result == nullptr) {
            throw JSException("Internal error: invalid instance of JSResultSet");
        }
        return result;
    }

    void JSResultSet::nextRow(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            int currentIndex = info.Holder()->GetInternalField(FIELD_CURRENT_INDEX)->Int32Value();
            int maxResult = info.Holder()->GetInternalField(FIELD_MAX_INDEX)->Int32Value();
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
            int currentIndex = info.Holder()->GetInternalField(FIELD_CURRENT_INDEX)->Int32Value();
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

    void JSResultSet::stringify(const v8::FunctionCallbackInfo<v8::Value> &info){
        Isolate *isolate = info.GetIsolate();
        try {
            ResultSet * resultSet = getPGResult(info);
            Value root(arrayValue);
            int nTuples = resultSet->numberOfRow();
            int nRow = resultSet->numberOfField();
            for(int tuple = 0; tuple < nTuples; tuple++){
                Value object(objectValue);
                for(int row=0; row < nRow; row++){
                    auto colName = resultSet->columnName(row);
                    if (colName == nullptr)
                        continue;
                    auto dbData = DBDataConverter::DBData(resultSet, tuple, row);
                    std::any value = DBDataConverter::getAnyValue(dbData);
                    object[colName] =  DBDataConverter::getStringValue(value);
                }
                root.append(object);
            }
            std::stringstream stream;
            stream << root << "\r\n";
            info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, stream.str().c_str()));
        } catch (std::exception &excp) {
            BOOST_LOG_TRIVIAL(error) << excp.what();
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    std::unique_ptr<DBRow> JSResultSet::makeDBRow(ResultSet *resultSet, uint currentIndex) {
        auto dbRow = std::make_unique<DBRow>();

        int fieldCount = resultSet->numberOfField();

        for (int colIndex = 0; colIndex < fieldCount; colIndex++) {
            auto fieldName = resultSet->columnName(colIndex);
            if (!resultSet->fieldIsNull(currentIndex, colIndex)) {
                DBDataConverter::DBData dbData(resultSet, currentIndex, colIndex);
                std::any value = DBDataConverter::getAnyValue(dbData);
                dbRow->setValue(fieldName, value);
            } else {
                dbRow->setValue(fieldName, std::any());
            }
        }

        return dbRow;
    }
}
