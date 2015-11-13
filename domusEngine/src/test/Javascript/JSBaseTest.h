/*
 * JSBaseTest.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSBASETEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSBASETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <v8.h>

#include <memory>

namespace zigbee {
namespace test {

#define V8_SETUP HandleScope handle_scope(isolate);\
				Local<Context> context = Context::New(isolate, nullptr);\
				Context::Scope context_scope(context);\
				Local<Object>  global = context->Global();


MATCHER(HasNoHasCaught, ""){
	if (arg.HasCaught()) {
		auto message = arg.Message();
		v8::String::Utf8Value utf8(message->Get());
		std::cout << "exception message: " << *utf8 << std::endl;
		return false;
	}
	return true;
}

class JSBaseTest : public ::testing::Test{
public:
	virtual ~JSBaseTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
	v8::Local<v8::Value> runScript(const std::string& script);
protected:
	std::unique_ptr<v8::Locker> locker;
	v8::Isolate * isolate;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSBASETEST_H_ */
