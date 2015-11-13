/*
 * JSLogTest.h
 *
 *  Created on: 19/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSLOGTEST_H_
#define SRC_TEST_JAVASCRIPT_JSLOGTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../JavaScript/JSLog.h"
#include "../../Utils/Log.h"

namespace zigbee {
namespace test {

class JSLogTest : public testing::Test {
public:
	virtual ~JSLogTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;

	v8::Local<v8::Value> runScript(const std::string& script);
protected:
	std::unique_ptr<v8::Locker> locker;
	v8::Isolate * isolate;

	std::shared_ptr<Log> log;
	std::shared_ptr<JSLog> jsLog;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSLOGTEST_H_ */
