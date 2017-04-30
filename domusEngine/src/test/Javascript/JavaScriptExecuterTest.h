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
#include "../Mocks/ClustersMock.h"
#include "../Mocks/http/RestHandlerMock.h"
#include "../../JavaScript/JavaScriptExecuter.h"


namespace zigbee {
    namespace test {

        class JavaScriptExecuterTest : public testing::Test {
        public:
            virtual ~JavaScriptExecuterTest()=default;

        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;

            ExtAddress convertFromString(const std::string &strExt);

        protected:
            std::unique_ptr<ZigbeeDeviceMock> zigbeeDevice;
            std::unique_ptr<http::RestHandlerMock> restHandler;
            SingletonObjectsMock singletonObjects;
            ClustersMock clustersMock;
            std::unique_ptr<ZDevicesMock> zDevices;
            std::unique_ptr<JavaScriptExecuter> jsExecuter;
            ExtAddress extAddress;
        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JAVASCRIPTEXECUTERTEST_H_ */
