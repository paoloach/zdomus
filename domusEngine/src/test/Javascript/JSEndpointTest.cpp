/*
 * JSEndpointTest.cpp
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "JSEndpointTest.h"
#include "../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace testing;
        using namespace v8;

        inline auto getConstructorName(Local<Object> & object){
            String::Utf8Value utf8Message(object->GetConstructorName());
            return std::string(*utf8Message);
        }

        static std::string EXTENDED_ADDRESS = "00-01-02-03-04-05-06-07";
        static constexpr NwkAddr NWK_ADDRESS{10};
        static constexpr EndpointID ENDPOINT_ID{23};
        static constexpr uint32_t PROFILE_ID{11};
        static constexpr uint32_t DEVICE_ID{12};
        static constexpr uint32_t DEVICE_VER{13};
        static const std::vector<ClusterID> IN_CLUSTERS{ClusterID {30}, ClusterID {31}};
        static const std::vector<ClusterID> OUT_CLUSTERS{ClusterID {35}, ClusterID {36}};
        static GenericMessage annunceMsg1{1};
        static AnnunceMessage ANNUNCE{annunceMsg1, 2, {3, 4, 5, 6, 7, 8, 9, 10}, 11};

#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr);\
                Context::Scope context_scope(context);\
                Local<Object>  global = context->Global(); \



        void JSEndpointTest::SetUp() {
            std::stringstream stream{};

            stream << "var a = " << JSZENDPOINT << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ");";
            creatingZDeviceScript = stream.str();

            extAddress = convertFromString(EXTENDED_ADDRESS);
            jsEndpoint = std::make_unique<JSZEndpoint>(&zDevices, &jszClusterMock);
            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);

            isolate->Enter();
            locker.reset(new Locker{isolate});
        }

        void JSEndpointTest::TearDown() {
            locker.reset();
            isolate->Exit();
            jsEndpoint.reset();
            isolate->Dispose();
        }

        v8::Local<v8::Value> JSEndpointTest::runScript(const std::string &script) {
            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            return jsScript->Run();
        }

        ExtAddress JSEndpointTest::convertFromString(const std::string &strExt) {
            ExtAddress extAddress{};
            std::stringstream stream{strExt};
            stream >> extAddress;
            return extAddress;
        }

        TEST_F(JSEndpointTest, createTemplate) {
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);

            Handle<Object> global = context->Global();
            jsEndpoint->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSEndpointTest, createIstance) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << JSZENDPOINT << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ");";
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsObject());
            Local<Object> object = result->ToObject();
            ASSERT_EQ(getConstructorName(object), JSZENDPOINT);
        }

        TEST_F(JSEndpointTest, getEndpointId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.endpointId");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUint32(), true);
            ASSERT_EQ(result->Uint32Value(), ENDPOINT_ID.getId());
        }

        TEST_F(JSEndpointTest, getProfileId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).TIMES(0,2).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.profileId");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUint32(), true);
            ASSERT_EQ(result->Uint32Value(), PROFILE_ID);
        }

        TEST_F(JSEndpointTest, getDeviceId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).TIMES(0,2).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.deviceId");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUint32(), true);
            ASSERT_EQ(result->Uint32Value(), DEVICE_ID);
        }

        TEST_F(JSEndpointTest, getDeviceVersion) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).TIMES(0,2).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.deviceVersion");
            ASSERT_EQ(result, Integer::New(isolate, DEVICE_VER).As<Object>());
        }


        TEST_F(JSEndpointTest, getCluster) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            int clusterId = 23;
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);
            Local<Object> cluster = Integer::New(isolate, 23).As<Object>();

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).TIMES(0,2).LR_RETURN(&zDevice);
            REQUIRE_CALL(jszClusterMock, createInstance(isolate, extAddress, ENDPOINT_ID, ClusterID(clusterId))).RETURN(cluster);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.getCluster(" + std::to_string(clusterId) + ");");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result, cluster);
        }


    } /* namespace test */
} /* namespace zigbee */
