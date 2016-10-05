/*
 * JSDevicesTest.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSDEVICESTEST_H_
#define SRC_TEST_JAVASCRIPT_JSDEVICESTEST_H_
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/JSZDeviceMock.h"
#include "../../JavaScript/JSZDevices.h"
#include "../../JavaScript/V8Allocator.h"

namespace zigbee {
namespace test {

class JSDevicesTest : public testing::Test{
public:
	virtual ~JSDevicesTest()=default;
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
protected:
	v8::Local<v8::Value> runScript(const std::string & script);
protected:
	V8Allocator v8Allocator;
	v8::Isolate::CreateParams createParams;
    std::unique_ptr<ZDevicesMock> zDevices;
	JSZDeviceMock_P jszDevice;
	std::unique_ptr<JSZDevices> jsDevices;
	v8::Isolate * isolate;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSDEVICESTEST_H_ */
