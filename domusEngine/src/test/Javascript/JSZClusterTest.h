/*
 * JSZClusterTest.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_
#define SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Mocks/JSZDeviceMock.h"
#include "../Mocks/JSZAttributeMock.h"
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/JSZAttributeFactoryMock.h"
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/ClustersMock.h"
#include "../../JavaScript/JSZCluster.h"
#include "../../JavaScript/V8Allocator.h"

namespace zigbee {
    namespace test {


        class JSZClusterTest : public testing::Test {
        public:
            ~JSZClusterTest() override = default;

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
            SingletonObjectsMock singletonObjectsMock;
            ZDevicesMock zDevices;
            ClustersMock clusters;
            ZigbeeDeviceMock zigbeeDevice;
            std::unique_ptr<JSZCluster> jsZCluster;
            ExtAddress extAddress;
            ClusterMock cluster;
            std::unique_ptr<ZCLAttributeMock> zclAttributeMock;
            JSZAttributeFactoryMock jsZAttributeFactory;
            std::unique_ptr<ZCLAttributeMock> defaultZclAttribute;
            ZDevice defaultZDevice;
        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_ */
