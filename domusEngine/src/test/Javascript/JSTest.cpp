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

using trompeloeil::_;

namespace zigbee {
    namespace test {

        using std::make_shared;
        using namespace v8;


        constexpr NwkAddr JSTest::NWK_ADDRESS;
        constexpr EndpointID JSTest::ENDPOINT_ID;
        constexpr ClusterID JSTest::CLUSTER_ID;
        constexpr uint32_t JSTest::PROFILE_ID;
        constexpr uint32_t JSTest::DEVICE_ID;
        constexpr uint32_t JSTest::DEVICE_VER;
        constexpr int32_t JSTest::ATTRIBUTE0_ID;
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

            defaultZclAttribute = std::make_unique<ZCLAttributeMock>();
            jsLog = std::make_shared<JSLog>();

            getZDevices = NAMED_ALLOW_CALL(singletonObjectsMock, getZDevices()).RETURN(zDevices.get());
            getClusters = NAMED_ALLOW_CALL(singletonObjectsMock, getClusters()).LR_RETURN(&clustersMock);
            getCluster = NAMED_ALLOW_CALL(clustersMock, getCluster(_,_,_)).LR_RETURN(&defaultCluster);
            getDevice = NAMED_ALLOW_CALL(*zDevices, getDevice(extAddress)).LR_RETURN(&defaultZDevice);
            exists = NAMED_ALLOW_CALL(*zDevices, exists(_)).RETURN(false);
            getAttribute = NAMED_ALLOW_CALL(cluster, getAttribute(ATTRIBUTE0_ID)).RETURN(zclAttributeMock.get());
        }

        void JSTest::TearDown() {
            getZDevices.release();
            getClusters.release();
            getCluster.release();
            getDevice.release();
            getAttribute.release();
            exists.release();
            locker.reset();
            jsLog->resetPersistences();
            isolate->Exit();
            isolate->Dispose();
            defaultZclAttribute.reset();
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
