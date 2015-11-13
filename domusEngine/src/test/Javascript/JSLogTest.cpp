/*
 * JSLogTest.cpp
 *
 *  Created on: 19/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSLogTest.h"
#include "../../JavaScript/JSObjects.h"

namespace zigbee {
namespace test {

using namespace testing;
using namespace v8;

#define V8_SETUP HandleScope handle_scope(isolate);\
				Local<Context> context = Context::New(isolate, nullptr);\
				Context::Scope context_scope(context);\
				Local<Object>  global = context->Global(); \

JSLogTest::~JSLogTest() {
}

void JSLogTest::SetUp() {

	log = std::make_shared<Log>();
	jsLog = std::make_shared<JSLog>(*log);

	isolate = v8::Isolate::New();

	isolate->Enter();
	locker.reset(new Locker { isolate });
}

void JSLogTest::TearDown() {
	locker.reset();
	isolate->Exit();
	jsLog->resetPersistences();
	isolate->Dispose();
}

v8::Local<v8::Value> JSLogTest::runScript(const std::string& script) {
	Local<String> source = String::NewFromUtf8(isolate, script.c_str());
	Local<Script> jsScript = Script::Compile(source);
	return jsScript->Run();
}

TEST_F( JSLogTest, createTemplate) {
	HandleScope handle_scope(isolate);
	Local<Context> context = Context::New(isolate, nullptr);
	Context::Scope context_scope(context);

	Handle<Object> global = context->Global();
	jsLog->initJsObjectsTemplate(isolate, global);
}

TEST_F( JSLogTest, createInstance) {
	std::stringstream stream;
	V8_SETUP
	jsLog->initJsObjectsTemplate(isolate, global);

	stream << "var log=" << JSLOG << "();";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
	ASSERT_TRUE(log->empty());
}

TEST_F( JSLogTest, debug) {
	std::string expectedMessage = "debug Message";
	std::stringstream stream;
	V8_SETUP
	jsLog->initJsObjectsTemplate(isolate, global);

	stream << "var log=" << JSLOG << "();";
	stream << "log.debug('" << expectedMessage << "');";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
	ASSERT_FALSE(log->empty());
	Log::LogData logData = log->get();
	ASSERT_THAT(logData.msg, StrEq(expectedMessage));
	ASSERT_THAT(logData.level, Eq(Log::DEBUG));
}

TEST_F( JSLogTest, info) {
	std::string expectedMessage = "info Message";
	std::stringstream stream;
	V8_SETUP
	jsLog->initJsObjectsTemplate(isolate, global);

	stream << "var log=" << JSLOG << "();";
	stream << "log.info('" << expectedMessage << "');";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
	ASSERT_FALSE(log->empty());
	Log::LogData logData = log->get();
	ASSERT_THAT(logData.msg, StrEq(expectedMessage));
	ASSERT_THAT(logData.level, Eq(Log::INFO));
}

TEST_F( JSLogTest, warning) {
	std::string expectedMessage = "warning Message";
	std::stringstream stream;
	V8_SETUP
	jsLog->initJsObjectsTemplate(isolate, global);

	stream << "var log=" << JSLOG << "();";
	stream << "log.warn('" << expectedMessage << "');";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
	ASSERT_FALSE(log->empty());
	Log::LogData logData = log->get();
	ASSERT_THAT(logData.msg, StrEq(expectedMessage));
	ASSERT_THAT(logData.level, Eq(Log::WARNING));
}

TEST_F( JSLogTest, error) {
	std::string expectedMessage = "error Message";
	std::stringstream stream;
	V8_SETUP
	jsLog->initJsObjectsTemplate(isolate, global);

	stream << "var log=" << JSLOG << "();";
	stream << "log.error('" << expectedMessage << "');";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
	ASSERT_FALSE(log->empty());
	Log::LogData logData = log->get();
	ASSERT_THAT(logData.msg, StrEq(expectedMessage));
	ASSERT_THAT(logData.level, Eq(Log::ERROR));
}
} /* namespace test */
} /* namespace zigbee */
