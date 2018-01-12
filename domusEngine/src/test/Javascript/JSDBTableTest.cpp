/*
 * JSDBTableTest.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "../../Database/Exceptions/DBExceptionNoTable.h"
#include "../../Database/Exceptions/DBException.h"
#include "../../JavaScript/JSObjects.h"

#include "JSDBTableTest.h"

namespace zigbee {
    namespace test {

        using trompeloeil::_;
        using namespace v8;

        using std::string;
        using std::stringstream;
        using std::any;
        using std::any_cast;

//        bool IsAnyString(std::string & expectedString, ) {
//            if (arg.type() == typeid(std::string)) {
//                std::string value = any_cast<std::string>(arg);
//                return value == expectedString;
//            }
//            return false;
//        }
//
//        MATCHER_P(IsAnyInt32, expectedValue, "") {
//            if (arg.type() == typeid(int32_t)) {
//                int32_t value = any_cast<int32_t>(arg);
//                return value == expectedValue;
//            }
//            return false;
//        }
//
//        MATCHER_P(IsAnyUInt32, expectedValue, "") {
//            if (arg.type() == typeid(uint32_t)) {
//                uint32_t value = any_cast<uint32_t>(arg);
//                return value == expectedValue;
//            }
//            return false;
//        }
//
//        MATCHER_P2(HasPair, expectedKey, expectedVal, "") {
//            return expectedVal == any_cast<string>(arg->getValue(expectedKey));
//        }

#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr);\
                Context::Scope context_scope(context);\
                Local<Object>  global = context->Global();

        void JSDBTableTest::SetUp() {
            JSBaseTest::SetUp();

            jsRow = std::make_unique<JSRow>();
            jsResultSet = std::make_unique<JSResultSet>(jsRow.get());

            jsDBTable = std::make_unique<JSDBTable>(dbTableFactoryMock, jsRow.get(), jsResultSet.get());

            getTable = NAMED_ALLOW_CALL(dbTableFactoryMock, getTable(_)).RETURN(nullptr);
            find = NAMED_ALLOW_CALL(dbTable, find(_)).RETURN(nullptr);
        }

        void JSDBTableTest::TearDown() {
            jsDBTable->resetPersistences();
            jsResultSet->resetPersistences();
            jsRow->resetPersistences();
            JSBaseTest::TearDown();
        }

        TEST_F(JSDBTableTest, createTemplate) {
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);

            Handle<Object> global = context->Global();
            jsRow->initJsObjectsTemplate(isolate, global);
            jsResultSet->initJsObjectsTemplate(isolate, global);
            jsDBTable->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSDBTableTest, createInstance) {

            string tableName = "table name";
            stringstream stream;
            V8_SETUP
            jsRow->initJsObjectsTemplate(isolate, global);
            jsResultSet->initJsObjectsTemplate(isolate, global);
            jsDBTable->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(dbTableFactoryMock, getTable(tableName)).RETURN(&dbTable);

            stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
            stream << "table;";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsObject());
            ASSERT_FALSE(tryCatch.HasCaught());
        }

        TEST_F(JSDBTableTest, createInvalidInstance) {

            string tableName = "no table name";
            stringstream stream;
            V8_SETUP
            jsRow->initJsObjectsTemplate(isolate, global);
            jsResultSet->initJsObjectsTemplate(isolate, global);
            jsDBTable->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(dbTableFactoryMock, getTable(tableName)).THROW(DBExceptionNoTable(tableName));

            stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
            stream << "table;";
            TryCatch tryCatch{};
            runScript(stream.str());
            ASSERT_TRUE(tryCatch.HasCaught());

        }

        TEST_F(JSDBTableTest, find) {
            string tableName = "table name";
            string query = "this s  a query";
            stringstream stream;
            PGresult * expectedRow = nullptr;
            V8_SETUP
            jsRow->initJsObjectsTemplate(isolate, global);
            jsResultSet->initJsObjectsTemplate(isolate, global);
            jsDBTable->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(dbTableFactoryMock, getTable(tableName)).RETURN(&dbTable);
            REQUIRE_CALL(dbTable, find(query)).RETURN(expectedRow);

            stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
            stream << "table.find('" << query << "');";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_FALSE(tryCatch.HasCaught());
            ASSERT_TRUE(result->IsObject());
            auto object = result.As<Object>();
            std::string name ( *String::Utf8Value(object));
            ASSERT_EQ(name, "[object DbResultSet]");
        }


        TEST_F(JSDBTableTest, insert) {
            string tableName = "table name";
            stringstream stream;
            string key = "key";
            string value = "value";
            V8_SETUP
            jsRow->initJsObjectsTemplate(isolate, global);
            jsResultSet->initJsObjectsTemplate(isolate, global);
            jsDBTable->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(dbTableFactoryMock, getTable(tableName)).RETURN(&dbTable);
            REQUIRE_CALL(dbTable, insert(_))
                .WITH(std::any_cast<std::string>(_1->getValue(key)) == value);

            stream << "var row = " << JSDBROW << "();";
            stream << "row.setValue('" << key << "','" << value << "');";
            stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
            stream << "table.insert(row);";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsUndefined());
            ASSERT_FALSE(tryCatch.HasCaught());
        }


    } /* namespace test */
} /* namespace zigbee */
