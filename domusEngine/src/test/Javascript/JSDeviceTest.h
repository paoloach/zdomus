/*
 * JSDeviceTest.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSDEVICETEST_H_
#define SRC_TEST_JAVASCRIPT_JSDEVICETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../JavaScript/V8Allocator.h"
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/JSZEndpointMock.h"
#include "../Mocks/JSZDeviceMock.h"
#include "../../JavaScript/JSZDevice.h"

namespace zigbee {
namespace test {

class JSDeviceTest : public testing::Test{
public:
    JSDeviceTest();
	virtual ~JSDeviceTest()=default;
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
	static void getDevice( const v8::FunctionCallbackInfo<v8::Value>& info);
	v8::Local<v8::Value> runScript(const std::string& script);
protected:
	V8Allocator v8Allocator;
	v8::Isolate::CreateParams createParams;
	std::unique_ptr<v8::Locker> locker;
	std::string	creatingZDeviceScript;
	v8::Isolate * isolate;
	std::unique_ptr<ZDevicesMock> zDevices;
	JSZEndpointMock_P jsEndpoint;
	JSZDevice_P jsDevice;
	ExtAddress extAddress;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSDEVICETEST_H_ */
