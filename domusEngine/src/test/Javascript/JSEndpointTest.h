/*
 * JSEndpointTest.h
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSENDPOINTTEST_H_
#define SRC_TEST_JAVASCRIPT_JSENDPOINTTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/JSZDeviceMock.h"
#include "../../JavaScript/JSZEndpoint.h"

namespace zigbee {
namespace test {

class JSEndpointTest : public testing::Test {
public:
	virtual ~JSEndpointTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
	v8::Local<v8::Value> runScript(const std::string& script);
	static ExtAddress convertFromString(const std::string & strExt);
protected:
	std::unique_ptr<v8::Locker> locker;
	std::string	creatingZDeviceScript;
	v8::Isolate * isolate;
	ZDevicesMock_P zDevices;
	JSZDeviceMock_P jszDevice;
	JSZEndpoint_P jsEndpoint;
	ExtAddress extAddress;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSENDPOINTTEST_H_ */
