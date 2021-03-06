/*
 * JSTest.h
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSTEST_H_
#define SRC_TEST_JAVASCRIPT_JSTEST_H_

#include <gtest/gtest.h>

#include <v8.h>
#include <zigbee/ExtAddress.h>
#include "../../JavaScript/JSLog.h"
#include "../../JavaScript/V8Allocator.h"
#include "../../ZigbeeData/ZDevice.h"
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/ClustersMock.h"
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"

namespace zigbee {
    namespace test {

        class JSTest : public testing::Test {
        protected:
            static const std::string EXTENDED_ADDRESS;
            static constexpr NwkAddr NWK_ADDRESS{10};
            static constexpr EndpointID ENDPOINT_ID{23};
            static constexpr ClusterID CLUSTER_ID{1};

            static constexpr uint32_t PROFILE_ID = 11;
            static constexpr uint32_t DEVICE_ID = 12;
            static constexpr uint32_t DEVICE_VER = 13;
            static const std::vector<ClusterID> IN_CLUSTERS;
            static const std::vector<ClusterID> OUT_CLUSTERS;

            static constexpr int32_t ATTRIBUTE0_ID{0};
            static constexpr uint32_t ATTRIBUTE1_ID{3};

        public:
            JSTest();

            virtual ~JSTest() = default;

        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;

            v8::Local<v8::Value> runScript(const std::string &script);

            static ExtAddress convertFromString(const std::string &strExt);

        protected:
            V8Allocator v8Allocator;
            v8::Isolate::CreateParams createParams;
            std::unique_ptr<v8::Locker> locker;
            v8::Isolate *isolate;
            std::unique_ptr<ZDevicesMock> zDevices;
            ExtAddress extAddress;
            SingletonObjectsMock singletonObjectsMock;
            ClustersMock clustersMock;
            std::unique_ptr<ZigbeeDeviceMock> zigbeeDeviceMock;
            ZigbeeDevice *zigbeeDevice;
            ClusterMock defaultCluster;
            ClusterMock cluster;
            std::unique_ptr<ZCLAttributeMock> zclAttributeMock;
            std::unique_ptr<ZCLAttributeMock> defaultZclAttribute;
            ZDevice defaultZDevice;
            std::shared_ptr<JSLog> jsLog;


            std::unique_ptr<trompeloeil::expectation> getZDevices;
            std::unique_ptr<trompeloeil::expectation> getClusters;
            std::unique_ptr<trompeloeil::expectation> getCluster;
            std::unique_ptr<trompeloeil::expectation> getDevice;
            std::unique_ptr<trompeloeil::expectation> exists;
            std::unique_ptr<trompeloeil::expectation> getAttribute;
        };

//        MATCHER_P(IsString, stringToCompare, "") {
//            char StringUTF[255]{};
//
//            arg->WriteUtf8(StringUTF, 255);
//            return stringToCompare == std::string(StringUTF);
//        }
//
//        MATCHER(IsTrue, "") {
//            return arg->ToBoolean()->Value();
//        }
//
//        MATCHER(IsFalse, "") {
//            return arg->ToBoolean()->Value() == false;
//        }

#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr);\
                Context::Scope context_scope(context);\
                Local<Object>  global = context->Global(); \

    }
/* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSTEST_H_ */
