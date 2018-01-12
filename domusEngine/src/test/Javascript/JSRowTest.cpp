/*
 * JSRowTest.cpp
 *
 *  Created on: 27/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <iostream>
#include "JSRowTest.h"
#include "../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace testing;
        using namespace v8;

        using std::string;
        using std::stringstream;
        using std::any;

        JSRowTest::~JSRowTest() {
        }

        void JSRowTest::SetUp() {
            JSBaseTest::SetUp();
        }

        void JSRowTest::TearDown() {
            JSBaseTest::TearDown();
        }

        TEST_F(JSRowTest, createTemplate) {
            JSRow jsRow;
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);

            Handle<Object> global = context->Global();
            jsRow.initJsObjectsTemplate(isolate, global);
            jsRow.resetPersistences();
        }

        TEST_F(JSRowTest, createInstance) {
            JSRow jsRow;
            stringstream stream;
            V8_SETUP
            jsRow.initJsObjectsTemplate(isolate, global);

            stream << "var row=" << JSDBROW << "();";
            stream << "row;";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsObject());
            ASSERT_FALSE(tryCatch.HasCaught());
        }

        TEST_F(JSRowTest, put_get_element_as_string) {
            JSRow jsRow;
            stringstream stream;
            string field1 = "field1";
            string value1 = "value1";

            string field2 = "field2";
            int value2 = 3;;
            V8_SETUP
            jsRow.initJsObjectsTemplate(isolate, global);

            stream << "var row=" << JSDBROW << "();\n";
            stream << "row.setValue('" << field1 << "','" << value1 << "');\n";
            stream << "row.setValue('" << field2 << "'," << value2 << ");\n";
            stream << "row.getValue('" << field1 << "');\n";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_TRUE(HasNoHasCaught(tryCatch));
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsString());
            v8::String::Utf8Value value(result);
            ASSERT_EQ(*value, value1);
        }

        TEST_F(JSRowTest, put_get_element_as_Date) {
            JSRow jsRow;
            stringstream stream;
            string field1 = "field1";
            int millisec = 360000022;

            V8_SETUP
            jsRow.initJsObjectsTemplate(isolate, global);

            stream << "var date = new Date(" << millisec << ");\n";
            stream << "var row=" << JSDBROW << "();\n";
            stream << "row.setValue('" << field1 << "',date);\n";
            stream << "var a = row.getValue('" << field1 << "');\n";
            stream << "a;\n";
//	stream << "a.valueOf()";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_TRUE(HasNoHasCaught(tryCatch));
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsDate());
            v8::String::Utf8Value value(result);

            result = runScript("a.valueOf();\n");
            ASSERT_TRUE(HasNoHasCaught(tryCatch));
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsNumber());
            ASSERT_EQ(result->NumberValue(), millisec);
        }

        TEST_F(JSRowTest, put_get_element_as_int) {
            JSRow jsRow;
            stringstream stream;
            string field1 = "field1";
            string value1 = "value1";
            string field2 = "field2";
            int value2 = 3;;
            V8_SETUP
            jsRow.initJsObjectsTemplate(isolate, global);

            stream << "var row=" << JSDBROW << "();\n";
            stream << "row.setValue('" << field1 << "','" << value1 << "');\n";
            stream << "row.setValue('" << field2 << "'," << value2 << ");\n";
            stream << "row.getValue('" << field2 << "');\n";
            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_TRUE( HasNoHasCaught(tryCatch));
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsInt32());
            ASSERT_EQ(result->Int32Value(), value2);
        }

        TEST_F(JSRowTest, assignement) {
            JSRow jsRow;
            stringstream stream;
            string field1 = "field1";
            string value1 = "value1";
            string field2 = "field2";
            int value2 = 3;;
            V8_SETUP
            jsRow.initJsObjectsTemplate(isolate, global);

            stream << "var row=" << JSDBROW << "();\n";
            stream << "row.setValue('" << field1 << "','" << value1 << "');\n";
            stream << "row.setValue('" << field2 << "'," << value2 << ");\n";
            stream << "var row2 = row;\n";
            stream << "var row3 = row2;\n";
            stream << "row3.getValue('" << field2 << "');\n";

            TryCatch tryCatch{};
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_TRUE( HasNoHasCaught(tryCatch));
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsInt32());
            ASSERT_EQ(result->Int32Value(), value2);
        }

    } /* namespace test */
} /* namespace zigbee */
