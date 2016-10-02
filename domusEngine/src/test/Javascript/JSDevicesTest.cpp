/*
 * JSDevicesTest.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include "JSDevicesTest.h"

namespace zigbee {
namespace test {

using namespace v8;
using namespace testing;

static  GenericMessage annunceMsg1 {1};
static  GenericMessage simpleeMsg {2};
static  AnnunceMessage annunce1 {annunceMsg1,2,{3,4,5,6,7,8,9,10},11};
static   AnnunceMessage annunce2 {annunceMsg1,102,{11,12,13,14,15,16,17,18},111};

JSDevicesTest::JSDevicesTest() : zDevices{ std::make_unique<ZDevicesMock>()}{;
}

void JSDevicesTest::SetUp() {
	jsDevices.reset(new JSZDevices{zDevices.get(),jszDevice} );
	createParams.array_buffer_allocator = &v8Allocator;
	isolate = v8::Isolate::New(createParams);
}

void JSDevicesTest::TearDown() {
	jsDevices.reset();
	isolate->Dispose();
}

TEST_F( JSDevicesTest, createTemplate) {
	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);
	Handle<ObjectTemplate> global = ObjectTemplate::New();
	jsDevices->initJsObjectsTemplate(isolate,global);
}

TEST_F( JSDevicesTest, createIstanceTemplate) {
	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);
	Local<Context> context = Context::New(isolate);
	Context::Scope context_scope(context);

	Local<Object> global = context->Global();



	EXPECT_CALL(*jszDevice.get(), initJsObjectsTemplate(isolate,global));
	jsDevices->initJsObjectsIstances(isolate,global);
	jsDevices->resetIstances();
}

TEST_F( JSDevicesTest, JSgetCountDevices) {
	int COUNT_DEVICES {3};
	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	jsDevices->initJsObjectsTemplate(isolate,global);

	Local<Context> context = Context::New(isolate,nullptr,global);
	Context::Scope context_scope(context);
	Local<Object> lGlobal = context->Global();
	EXPECT_CALL(*jszDevice.get(), initJsObjectsTemplate(isolate,lGlobal));
	jsDevices->initJsObjectsIstances(isolate,lGlobal);

	EXPECT_CALL(*zDevices.get(), getNumDevices()).WillOnce(Return(COUNT_DEVICES));

	v8::Local<v8::Value> result = runScript("zDevices.getCountDevices();");

	ASSERT_THAT(result->IsInt32(),true);
	v8::Local<Integer> count = Local<Integer>::Cast(result);
	ASSERT_THAT(count->Value(), COUNT_DEVICES);

	jsDevices->resetIstances();
}


TEST_F( JSDevicesTest, JSgetDevices) {
	ZDevice zDevice1{annunce1};
	ZDevice zDevice2{annunce2};
	std::vector<ZDevice *> devices {&zDevice1, &zDevice2};

	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	jsDevices->initJsObjectsTemplate(isolate,global);

	Local<Context> context = Context::New(isolate,nullptr,global);
	Context::Scope context_scope(context);
	Local<Object> lGlobal = context->Global();
	EXPECT_CALL(*jszDevice.get(), initJsObjectsTemplate(isolate,lGlobal));
	jsDevices->initJsObjectsIstances(isolate,lGlobal);

	Local<v8::Object> defaultObj = Object::New( isolate);
	Local<v8::Object> expectedJSZDevice1 = Object::New( isolate);
	Local<v8::Object> expectedJSZDevice2 = Object::New( isolate);


	ON_CALL(*jszDevice.get(),  createInstance(_, _)).WillByDefault(Return(defaultObj));
	EXPECT_CALL(*zDevices.get(), getDevices()).WillOnce(Return(devices));
	EXPECT_CALL(*jszDevice.get(), createInstance(isolate, zDevice1.getExtAddr())).WillOnce(Return(expectedJSZDevice1));
	EXPECT_CALL(*jszDevice.get(), createInstance(isolate, zDevice2.getExtAddr())).WillOnce(Return(expectedJSZDevice2));

	v8::Local<v8::Value> result = runScript("zDevices.getDevices();");

	ASSERT_THAT(result->IsArray(),true);
	v8::Local<Array> array = Local<Array>::Cast(result);
	ASSERT_THAT(array->Length(), 2);

	Local<Object> jszDevice1 = Local<Object>::Cast(array->Get(0));
	Local<Object> jszDevice2 = Local<Object>::Cast(array->Get(1));

	ASSERT_THAT(jszDevice1->GetIdentityHash(), Eq(expectedJSZDevice1->GetIdentityHash()));
	ASSERT_THAT(jszDevice2->GetIdentityHash(), Eq(expectedJSZDevice2->GetIdentityHash()));

	jsDevices->resetIstances();
}

TEST_F( JSDevicesTest, JSgetDeviceExist) {
	ZDevice zDevice{annunce1};
	std::stringstream stream {};

	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	jsDevices->initJsObjectsTemplate(isolate,global);

	Local<Context> context = Context::New(isolate,nullptr,global);
	Context::Scope context_scope(context);
	Local<Object> lGlobal = context->Global();
	EXPECT_CALL(*jszDevice.get(), initJsObjectsTemplate(isolate,lGlobal));
	jsDevices->initJsObjectsIstances(isolate,lGlobal);

	Local<v8::Object> defaultObj = Object::New( isolate);
	Local<v8::Object> expectedJSZDevice = Object::New( isolate);


	ON_CALL(*jszDevice.get(),  createInstance(_, _)).WillByDefault(Return(defaultObj));
	EXPECT_CALL(*zDevices.get(), exists(zDevice.getExtAddr())).WillOnce(Return(true));
	EXPECT_CALL(*jszDevice.get(), createInstance(isolate, zDevice.getExtAddr())).WillOnce(Return(expectedJSZDevice));

	stream << "zDevices.getDevice('" << zDevice.getExtAddr() << "');";
	v8::Local<v8::Value> result = runScript(stream.str());

	ASSERT_THAT(result.IsEmpty(),false);
	ASSERT_THAT(result->IsObject(),true);
	v8::Local<Object> object = Local<Object>::Cast(result);


	ASSERT_THAT(object->GetIdentityHash(), Eq(expectedJSZDevice->GetIdentityHash()));

	jsDevices->resetIstances();
}

TEST_F( JSDevicesTest, JSgetDeviceNotExist) {
	ZDevice zDevice{annunce1};
	std::stringstream stream {};

	Isolate::Scope isolate_scope(isolate);
	Locker locker(isolate);
	HandleScope handle_scope(isolate);

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	jsDevices->initJsObjectsTemplate(isolate,global);

	Local<Context> context = Context::New(isolate,nullptr,global);
	Context::Scope context_scope(context);
	Local<Object> lGlobal = context->Global();
	EXPECT_CALL(*jszDevice.get(), initJsObjectsTemplate(isolate,lGlobal));
	jsDevices->initJsObjectsIstances(isolate,lGlobal);

	Local<v8::Object> defaultObj = Object::New( isolate);


	ON_CALL(*jszDevice.get(),  createInstance(_, _)).WillByDefault(Return(defaultObj));
	EXPECT_CALL(*zDevices.get(), exists(zDevice.getExtAddr())).WillOnce(Return(false));

	TryCatch trycatch {};
	stream << zDevice.getExtAddr();
	v8::Local<v8::Value> result = runScript("zDevices.getDevice('" + stream.str() + "');");

	ASSERT_THAT(result.IsEmpty(),true);
	ASSERT_THAT(trycatch.HasCaught(),true);
	Local<v8::Value> exception = trycatch.Exception();
	v8::String::Utf8Value exception_str(exception);
	ASSERT_THAT(*exception_str, HasSubstr(stream.str()));


	jsDevices->resetIstances();
}

v8::Local<v8::Value> JSDevicesTest::runScript(const std::string& script) {
	Local<String> source = String::NewFromUtf8(isolate, script.c_str());
	Local<Script> jsScript = Script::Compile(source);
	return jsScript->Run();
}

} /* namespace test */
} /* namespace zigbee */
