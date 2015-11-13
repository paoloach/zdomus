/*
 * JSBaseTest.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSBaseTest.h"

namespace zigbee {
namespace test {


using namespace testing;
using namespace v8;

JSBaseTest::~JSBaseTest() {
}

void JSBaseTest::SetUp() {
	isolate = v8::Isolate::New();

	isolate->Enter();
	locker.reset(new Locker { isolate });
}

void JSBaseTest::TearDown() {
	locker.reset();
	isolate->Exit();
	isolate->Dispose();
}

v8::Local<v8::Value> JSBaseTest::runScript(const std::string& script) {
	Local<String> source = String::NewFromUtf8(isolate, script.c_str());
	Local<Script> jsScript = Script::Compile(source);
	return jsScript->Run();
}

} /* namespace test */
} /* namespace zigbee */
