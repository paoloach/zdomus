//
// Created by paolo on 27/12/16.
//

#include "JSEndpointsTest.h"
#include "../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {
        using namespace v8;
        using namespace testing;


#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr,globalTemplate);\
                Context::Scope context_scope(context);


        static ExtAddress EXTENDED_ADDRESS1{0,1,2,3,4,5,6,7,8};
        static constexpr NwkAddr NWK_ADDRESS1{10};
        static ExtAddress EXTENDED_ADDRESS2{0,1,2,3,4,5,6,7,9};
        static constexpr NwkAddr NWK_ADDRESS2{20};
        static ExtAddress EXTENDED_ADDRESS3{0,1,2,3,4,5,6,7,10};
        static constexpr NwkAddr NWK_ADDRESS3{30};

        static const std::vector<ClusterID> IN_CLUSTERS1{ClusterID {30}, ClusterID {31}};
        static const std::vector<ClusterID> OUT_CLUSTERS1{ClusterID {35}, ClusterID {36}};
        static const std::vector<ClusterID> IN_CLUSTERS2{ClusterID {30}, ClusterID {32}};
        static const std::vector<ClusterID> OUT_CLUSTERS2{ClusterID {35}, ClusterID {37}};
        static const std::vector<ClusterID> IN_CLUSTERS3{ClusterID {33}, ClusterID {34}};
        static const std::vector<ClusterID> OUT_CLUSTERS3{ClusterID {38}, ClusterID {39}};

        static const EndpointID epID1{1};
        static const EndpointID epID2{2};
        static const EndpointID epID3{3};

        static const ZEndpoint ENDPOINT1(NWK_ADDRESS1, epID1, 10 , 0,0, IN_CLUSTERS1, OUT_CLUSTERS1);
        static const ZEndpoint ENDPOINT2(NWK_ADDRESS2, epID2, 10 , 0,0, IN_CLUSTERS2, OUT_CLUSTERS2);
        static const ZEndpoint ENDPOINT3(NWK_ADDRESS3, epID3, 10 , 0,0, IN_CLUSTERS3, OUT_CLUSTERS3);

        static  ZDevice DEVICE1(EXTENDED_ADDRESS1, NWK_ADDRESS1, 0, {ENDPOINT1});
        static  ZDevice DEVICE2(EXTENDED_ADDRESS2, NWK_ADDRESS2, 0, {ENDPOINT2});
        static  ZDevice DEVICE3(EXTENDED_ADDRESS3, NWK_ADDRESS3, 0, {ENDPOINT3});
        static const std::vector<ZDevice *> zDevices = {&DEVICE1,&DEVICE2,&DEVICE3};

        void JSEndpointsTest::SetUp() {
            jsEndpoints = std::make_unique<JSZEndpoints>(&singletonObjectsMock, &jszEndpointMock);
            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
            isolate->Enter();
            locker.reset(new Locker{isolate});

            getZDevices = NAMED_ALLOW_CALL(singletonObjectsMock, getZDevices()).RETURN(&zDevicesMock);
            getDevices = NAMED_ALLOW_CALL(zDevicesMock, getDevices()).RETURN(zDevices);
        }

        void JSEndpointsTest::TearDown() {
            locker.reset();
            getZDevices.release();
            getDevices.release();
            isolate->Exit();
            jsEndpoints.reset();
            isolate->Dispose();
        }

        v8::Local<v8::Value> JSEndpointsTest::runScript(const std::string &script) {
            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            return jsScript->Run();
        }

        TEST_F(JSEndpointsTest, getEndpointWithInCluster) {
            Isolate::Scope isolate_scope(isolate);
            Locker locker(isolate);
            HandleScope handle_scope(isolate);

            Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New();
            jsEndpoints->initJsObjectsTemplate(isolate,globalTemplate);
            Local<Context> context = Context::New(isolate, nullptr, globalTemplate);
            Context::Scope context_scope(context);
            jsEndpoints->initJsObjectsInstance(isolate);

            Local<Object> endpoint1 = v8::Integer::New(isolate, 10).As<Object>();
            Local<Object> endpoint2 = v8::Integer::New(isolate, 20).As<Object>();

            REQUIRE_CALL(jszEndpointMock, createInstance(isolate, EXTENDED_ADDRESS1, epID1)).RETURN(endpoint1);
            REQUIRE_CALL(jszEndpointMock, createInstance(isolate, EXTENDED_ADDRESS2, epID2)).RETURN(endpoint2);

            std::stringstream stream;

            stream <<  JSZENDPOINTS << "." << GET_ENDPOINTS_WITH_IN_CLUSTER << "(" << IN_CLUSTERS1[0].getId() << ");";
            std::cout << "js=" << stream.str() << std::endl;
            auto creatingZDeviceScript = stream.str();
            TryCatch tryCatch;
            v8::Local<v8::Value> result = runScript(creatingZDeviceScript);
            if (tryCatch.HasCaught()) {
                String::Utf8Value utf8Message(tryCatch.Message()->Get());
                FAIL() << (*utf8Message);
            }
            ASSERT_FALSE(result.IsEmpty());
            ASSERT_TRUE(result->IsArray());
            Local<Array> array = result.As<Array>();
            ASSERT_EQ(array->Length(), 2);
            ASSERT_EQ(array->Get(0), endpoint1);
            ASSERT_EQ(array->Get(1), endpoint2);
        }

    }
}