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
#include "../Mocks/JSZClusterMock.h"
#include "../../JavaScript/JSZEndpoint.h"
#include "../../JavaScript/V8Allocator.h"

namespace zigbee {
    namespace test {

        class JSEndpointTest : public testing::Test {
        public:
            JSEndpointTest()=default;

            virtual ~JSEndpointTest() = default;

        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;

            v8::Local<v8::Value> runScript(const std::string &script);

            static ExtAddress convertFromString(const std::string &strExt);

        protected:
            V8Allocator v8Allocator;
            v8::Isolate::CreateParams createParams;
            std::unique_ptr<v8::Locker> locker;
            std::string creatingZDeviceScript;
            v8::Isolate *isolate;
            ZDevicesMock zDevices;
            JSZDeviceMock jszDevice;
            std::unique_ptr<JSZEndpoint> jsEndpoint;
            ExtAddress extAddress;
            JSZClusterMock jszClusterMock;
        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSENDPOINTTEST_H_ */
