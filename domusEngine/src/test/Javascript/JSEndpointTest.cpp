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

        MATCHER_P(IsString, stringToCompare, "") {
            char StringUTF[255]{};

            arg->WriteUtf8(StringUTF, 255);
            return stringToCompare == std::string(StringUTF);
        }

        MATCHER(IsTrue, "") {
            return arg->ToBoolean()->Value();
        }

        MATCHER(IsFalse, "") {
            return arg->ToBoolean()->Value() == false;
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

            stream << "var a = " << JSZENDPOINT << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ");";
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
            stream << JSZENDPOINT << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ");";
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_THAT(object->GetConstructorName(), IsString(JSZENDPOINT));
        }

        TEST_F(JSEndpointTest, getEndpointId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.endpointId");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            ASSERT_THAT(result->Uint32Value(), ENDPOINT_ID.getId());
        }

        TEST_F(JSEndpointTest, getProfileId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillRepeatedly(Return(&zDevice));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.profileId");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            ASSERT_THAT(result->Uint32Value(), PROFILE_ID);
        }

        TEST_F(JSEndpointTest, getDeviceId) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillRepeatedly(Return(&zDevice));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.deviceId");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            ASSERT_THAT(result->Uint32Value(), DEVICE_ID);
        }

        TEST_F(JSEndpointTest, getDeviceVersion) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillRepeatedly(Return(&zDevice));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.deviceVersion");
            ASSERT_THAT(result, Integer::New(isolate, DEVICE_VER).As<Object>());
        }


        TEST_F(JSEndpointTest, getCluster) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            int clusterId = 23;
            V8_SETUP
            jsEndpoint->initJsObjectsTemplate(isolate, global);
            Local<Object> cluster = Integer::New(isolate, 23).As<Object>();

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillRepeatedly(Return(&zDevice));
            EXPECT_CALL(jszClusterMock, createInstance(isolate, extAddress, ENDPOINT_ID, ClusterID(clusterId))).WillOnce(Return(cluster));

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.getCluster(" + std::to_string(clusterId) + ");");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result, cluster);
        }


    } /* namespace test */
} /* namespace zigbee */
