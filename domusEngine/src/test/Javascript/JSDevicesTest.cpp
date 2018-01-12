/*
 * JSDevicesTest.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include "JSDevicesTest.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using trompeloeil::_;

        static GenericMessage annunceMsg1{1};
        static AnnunceMessage annunce1{annunceMsg1, 2, {3, 4, 5, 6, 7, 8, 9, 10}, 11};
        static AnnunceMessage annunce2{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 111};

        void JSDevicesTest::SetUp() {
            zDevices = std::make_unique<ZDevicesMock>();
            jsDevices = std::make_unique<JSZDevices>(zDevices.get(), &jszDevice);
            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
        }

        void JSDevicesTest::TearDown() {
            jsDevices.reset();
            isolate->Dispose();
            zDevices.reset();
        }

        TEST_F(JSDevicesTest, createTemplate) {
            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);
            Handle<ObjectTemplate> global = ObjectTemplate::New();
            jsDevices->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSDevicesTest, createIstanceTemplate) {
            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate);
            Context::Scope context_scope(context);

            Local<Object> global = context->Global();


            REQUIRE_CALL(jszDevice, initJsObjectsTemplate(isolate, global));
            jsDevices->initJsObjectsIstances(isolate, global);
            jsDevices->resetIstances();
        }

        TEST_F(JSDevicesTest, JSgetCountDevices) {
            int COUNT_DEVICES{3};
            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);

            Handle<ObjectTemplate> global = ObjectTemplate::New();

            jsDevices->initJsObjectsTemplate(isolate, global);

            Local<Context> context = Context::New(isolate, nullptr, global);
            Context::Scope context_scope(context);
            Local<Object> lGlobal = context->Global();
            REQUIRE_CALL(jszDevice, initJsObjectsTemplate(isolate, lGlobal));
            jsDevices->initJsObjectsIstances(isolate, lGlobal);

            REQUIRE_CALL(*zDevices.get(), getNumDevices()).RETURN(COUNT_DEVICES);

            v8::Local<v8::Value> result = runScript("zDevices.getCountDevices();");

            ASSERT_TRUE(result->IsInt32());
            v8::Local<Integer> count = Local<Integer>::Cast(result);
            ASSERT_EQ(count->Value(), COUNT_DEVICES);

            jsDevices->resetIstances();
        }


        TEST_F(JSDevicesTest, JSgetDevices) {
            ZDevice zDevice1{annunce1};
            ZDevice zDevice2{annunce2};
            std::vector<ZDevice *> devices{&zDevice1, &zDevice2};

            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);

            Handle<ObjectTemplate> global = ObjectTemplate::New();

            jsDevices->initJsObjectsTemplate(isolate, global);

            Local<Context> context = Context::New(isolate, nullptr, global);
            Context::Scope context_scope(context);
            Local<Object> lGlobal = context->Global();
            REQUIRE_CALL(jszDevice, initJsObjectsTemplate(isolate, lGlobal));
            jsDevices->initJsObjectsIstances(isolate, lGlobal);

            Local<v8::Object> defaultObj = Object::New(isolate);
            Local<v8::Object> expectedJSZDevice1 = Object::New(isolate);
            Local<v8::Object> expectedJSZDevice2 = Object::New(isolate);


            ALLOW_CALL(jszDevice, createInstance(_, _)).RETURN(defaultObj);
            REQUIRE_CALL(*zDevices.get(), getDevices()).RETURN(devices);
            REQUIRE_CALL(jszDevice, createInstance(isolate, zDevice1.getExtAddr())).RETURN(expectedJSZDevice1);
            REQUIRE_CALL(jszDevice, createInstance(isolate, zDevice2.getExtAddr())).RETURN(expectedJSZDevice2);

            v8::Local<v8::Value> result = runScript("zDevices.getDevices();");

            ASSERT_TRUE(result->IsArray());
            v8::Local<Array> array = Local<Array>::Cast(result);
            ASSERT_EQ(array->Length(), 2);

            Local<Object> jszDevice1 = Local<Object>::Cast(array->Get(0));
            Local<Object> jszDevice2 = Local<Object>::Cast(array->Get(1));

            ASSERT_EQ(jszDevice1->GetIdentityHash(), expectedJSZDevice1->GetIdentityHash());
            ASSERT_EQ(jszDevice2->GetIdentityHash(), expectedJSZDevice2->GetIdentityHash());

            jsDevices->resetIstances();
        }

        TEST_F(JSDevicesTest, JSgetDeviceExist) {
            ZDevice zDevice{annunce1};
            std::stringstream stream{};

            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);

            Handle<ObjectTemplate> global = ObjectTemplate::New();

            jsDevices->initJsObjectsTemplate(isolate, global);

            Local<Context> context = Context::New(isolate, nullptr, global);
            Context::Scope context_scope(context);
            Local<Object> lGlobal = context->Global();
            REQUIRE_CALL(jszDevice, initJsObjectsTemplate(isolate, lGlobal));
            jsDevices->initJsObjectsIstances(isolate, lGlobal);

            Local<v8::Object> defaultObj = Object::New(isolate);
            Local<v8::Object> expectedJSZDevice = Object::New(isolate);


            ALLOW_CALL(jszDevice, createInstance(_, _)).RETURN(defaultObj);
            REQUIRE_CALL(*zDevices.get(), exists(zDevice.getExtAddr())).RETURN(true);
            REQUIRE_CALL(jszDevice, createInstance(isolate, zDevice.getExtAddr())).RETURN(expectedJSZDevice);

            stream << "zDevices.getDevice('" << zDevice.getExtAddr() << "');";
            v8::Local<v8::Value> result = runScript(stream.str());

            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsObject());
            v8::Local<Object> object = Local<Object>::Cast(result);


            ASSERT_EQ(object->GetIdentityHash(), expectedJSZDevice->GetIdentityHash());

            jsDevices->resetIstances();
        }

        TEST_F(JSDevicesTest, JSgetDeviceNotExist) {
            ZDevice zDevice{annunce1};
            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);

            Handle<ObjectTemplate> global = ObjectTemplate::New();

            jsDevices->initJsObjectsTemplate(isolate, global);

            Local<Context> context = Context::New(isolate, nullptr, global);
            Context::Scope context_scope(context);
            Local<Object> lGlobal = context->Global();
            REQUIRE_CALL(jszDevice, initJsObjectsTemplate(isolate, lGlobal));
            jsDevices->initJsObjectsIstances(isolate, lGlobal);

            Local<v8::Object> defaultObj = Object::New(isolate);


            ALLOW_CALL(jszDevice, createInstance(_, _)).RETURN(defaultObj);
            REQUIRE_CALL(*zDevices.get(), exists(zDevice.getExtAddr())).RETURN(false);

            TryCatch trycatch{};
            v8::Local<v8::Value> result = runScript("zDevices.getDevice('" + zDevice.getExtAddr().asString() + "');");

            ASSERT_TRUE(result.IsEmpty());
            ASSERT_TRUE(trycatch.HasCaught());
            Local<v8::Value> exception = trycatch.Exception();
            v8::String::Utf8Value exception_str(exception);
            //ASSERT_EQ(*exception_str, HasSubstr(zDevice.getExtAddr().asString()));


            jsDevices->resetIstances();
        }

        v8::Local<v8::Value> JSDevicesTest::runScript(const std::string &script) {
            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            return jsScript->Run();
        }

    } /* namespace test */
} /* namespace zigbee */
