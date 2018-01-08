/*
 * JSTest.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */
#include <memory>
#include "JSTest.h"

#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"

namespace zigbee {
    namespace test {

        using std::make_shared;
        using namespace v8;
        using namespace testing;

        constexpr NwkAddr JSTest::NWK_ADDRESS;
        constexpr EndpointID JSTest::ENDPOINT_ID;
        constexpr ClusterID JSTest::CLUSTER_ID;
        constexpr uint32_t JSTest::PROFILE_ID;
        constexpr uint32_t JSTest::DEVICE_ID;
        constexpr uint32_t JSTest::DEVICE_VER;
        constexpr uint32_t JSTest::ATTRIBUTE0_ID;
        constexpr uint32_t JSTest::ATTRIBUTE1_ID;

        const std::string JSTest::EXTENDED_ADDRESS = "00-01-02-03-04-05-06-07";
        const std::vector<ClusterID> JSTest::IN_CLUSTERS{ClusterID {1}, ClusterID {2}};
        const std::vector<ClusterID> JSTest::OUT_CLUSTERS{ClusterID {3}, ClusterID {4}};

        JSTest::JSTest() : zDevices{std::make_unique<ZDevicesMock>()} {

        }

        void JSTest::SetUp() {
            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
            isolate->Enter();
            locker.reset(new Locker{isolate});

            extAddress = convertFromString(EXTENDED_ADDRESS);

            zigbeeDeviceMock = std::make_unique<ZigbeeDeviceMock>();
            zigbeeDevice = zigbeeDeviceMock.get();

            defaultCluster = make_shared<ClusterMock>();
            defaultZclAttribute = std::make_unique<ZCLAttributeMock>();
            cluster = make_shared<ClusterMock>();
            jsLog = std::make_shared<JSLog>();

            EXPECT_CALL(singletonObjectsMock, getZDevices()).Times(AtLeast(0)).WillRepeatedly(Return(zDevices.get()));
            EXPECT_CALL(singletonObjectsMock, getClusters()).Times(AtLeast(0)).WillRepeatedly(Return(&clustersMock));
            ON_CALL(clustersMock, getCluster(_, _, _)).WillByDefault(Return(defaultCluster));
            ON_CALL(*zDevices, getDevice(extAddress)).WillByDefault(Return(&defaultZDevice));
            ON_CALL(*zDevices, exists(_)).WillByDefault(Return(false));
            ON_CALL(*cluster, getAttribute(ATTRIBUTE0_ID)).WillByDefault(Return(zclAttributeMock.get()));
        }

        void JSTest::TearDown() {
            locker.reset();
            jsLog->resetPersistences();
            isolate->Exit();
            isolate->Dispose();
            defaultZclAttribute.reset();
            defaultCluster.reset();
        }

        v8::Local<v8::Value> JSTest::runScript(const std::string &script) {
            std::cout << "script: \n" << script << "\n";

            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            TryCatch tryCatch;
            v8::Local<v8::Value> result = jsScript->Run();

            if (tryCatch.HasCaught()) {
                String::Utf8Value utf8Message(tryCatch.Message()->Get());
                std::cerr << "javascript thrown exception: " << *utf8Message;
            }
            return result;
        }

        ExtAddress JSTest::convertFromString(const std::string &strExt) {
            ExtAddress extAddress{};
            std::stringstream stream{strExt};
            stream >> extAddress;
            return extAddress;
        }

    } /* namespace test */
} /* namespace zigbee */
