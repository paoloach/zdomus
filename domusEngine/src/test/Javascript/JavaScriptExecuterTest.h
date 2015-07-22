/*
 * JavaScriptExecuterTest.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JAVASCRIPTEXECUTERTEST_H_
#define SRC_TEST_JAVASCRIPT_JAVASCRIPTEXECUTERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/SingletonObjectsMock.h"
#include "../../JavaScript/JavaScriptExecuter.h"

namespace zigbee {
namespace test {



class JavaScriptExecuterTest  : public  testing::Test{
public:
	virtual ~JavaScriptExecuterTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
	ExtAddress convertFromString(const std::string& strExt);
protected:
	std::shared_ptr<ZigbeeDeviceMock> zigbeeDevice;
	SingletonObjectsMock singletonObjects;
	ZDevicesMock_P zDevices;
	std::shared_ptr<JavaScriptExecuter> jsExecuter;
	ExtAddress extAddress;
	std::shared_ptr<http::FixedPathContainer> fixedPathContainer;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JAVASCRIPTEXECUTERTEST_H_ */