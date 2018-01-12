/*
 * JSZClusterTest.cpp
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#include <iomanip>

#include "JSZClusterTest.h"

#include "../../JavaScript/JSObjects.h"
#include "../Mocks/ClusterMock.h"
#include <sstream>

namespace zigbee {

    std::ostream  & operator<<(std::ostream & out,  ZCLAttribute *  attribute){
        out << "attribute" << attribute->getName();
        return out;
    }

    namespace test {
        using std::make_unique;
        using namespace v8;
        using trompeloeil::_;

#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr);\
                Context::Scope context_scope(context);\
                Local<Object>  global = context->Global(); \

        static std::string EXTENDED_ADDRESS = "00-01-02-03-04-05-06-07";
        static constexpr NwkAddr NWK_ADDRESS{10};
        static EndpointID ENDPOINT_ID{23};
        static constexpr ClusterID CLUSTER_ID{1};

        static constexpr uint32_t PROFILE_ID{11};
        static constexpr uint32_t DEVICE_ID{12};
        static constexpr uint32_t DEVICE_VER{13};
        static const std::vector<ClusterID> IN_CLUSTERS{ClusterID{1}, ClusterID{2}};
        static const std::vector<ClusterID> OUT_CLUSTERS{ClusterID{3}, ClusterID{4}};

        static constexpr uint32_t ATTRIBUTE0_ID{0};
        static constexpr uint32_t ATTRIBUTE1_ID{3};
        static constexpr uint32_t COMAND0_ID{1};
        static constexpr uint32_t COMAND1_ID{2};
        static constexpr uint32_t COMAND2_ID{3};
        static constexpr uint16_t COMAND1_ARG0{4};
        static constexpr const char *COMAND1_ARG1{"arg1"};
        static constexpr const char *ATTRIBUTE0_NAME{"Measured Value"};
        static constexpr const char *ATTRIBUTE1_NAME{"Tolerance"};

        static const std::vector<Cluster::AttributeDef> ATTRIBUTES_DEF = {Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, ATTRIBUTE0_ID, ATTRIBUTE0_NAME, true),
                                                                          Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16,
                                                                                                ATTRIBUTE1_ID, ATTRIBUTE1_NAME, true)};
        static std::shared_ptr<ClusterCmdParamsBase> COMAND_PARAM_UINT16 = std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("integer");
        static std::shared_ptr<ClusterCmdParamsBase> COMAND_PARAM_STRING = std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("string");
        static std::shared_ptr<ClusterCmdParamsBase> COMAND_PARAM_LIST_UINT16 = std::make_shared<ClusterCmdListParams<ZCLTypeDataType::ZCLTypeUInt16>>("array of uint16");


        inline auto getCmdData(uint16_t arg1, const char * arg2){
            ZCLType<ZCLTypeDataType::ZCLTypeUInt16> typeP1;
            ZCLType<ZCLTypeDataType::ZCLTypeStringChar> typeP2;
            std::vector<uint8_t> p1Data { typeP1.getRaw(arg1) };
            std::vector<uint8_t> p2Data { typeP2.getRaw(arg2) };
            std::vector<uint8_t> expected;
            std::copy(p1Data.begin(), p1Data.end(), std::back_inserter(expected));
            std::copy(p2Data.begin(), p2Data.end(), std::back_inserter(expected));

            return expected;
        }

        inline auto getCmdData(uint16_t arg1, uint16_t arg2){
            ZCLType<ZCLTypeDataType::ZCLTypeUInt16> typeP1;
            ZCLType<ZCLTypeDataType::ZCLTypeUInt16> typeP2;
            std::vector<uint8_t> p1Data { typeP1.getRaw(arg1) };
            std::vector<uint8_t> p2Data { typeP2.getRaw(arg2) };
            std::vector<uint8_t> expected;
            std::copy(p1Data.begin(), p1Data.end(), std::back_inserter(expected));
            std::copy(p2Data.begin(), p2Data.end(), std::back_inserter(expected));

            return expected;
        }

        template<typename A, typename B>
        inline auto dataIsFormedBy(A arg1, B arg2) {
            return trompeloeil::make_matcher<std::vector<uint8_t >>(
              [arg1, arg2](std::vector<uint8_t> toCheck){
                  return toCheck == getCmdData(arg1, arg2);
                },
              [arg1, arg2](std::ostream & os){
                  os << "expected a vector data of: [";
                  auto dataVector = getCmdData(arg1, arg2);
                  for (auto data: dataVector){
                      os << std::ios::hex << data << ", ";
                  }
                  os << "]";
              }

            );
        }

        auto inline toString(Local<String> arg) {
            v8::String::Utf8Value utf8Value(arg);
            return std::string(*utf8Value);
        }


        void JSZClusterTest::SetUp() {
            getZDevices = NAMED_ALLOW_CALL(singletonObjectsMock, getZDevices()).LR_RETURN(&zDevices);
            getClusters = NAMED_ALLOW_CALL(singletonObjectsMock, getClusters()).LR_RETURN(&clusters);
            zDeviceExists = NAMED_ALLOW_CALL(zDevices, exists(_)).RETURN(false);

            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
            isolate->Enter();
            locker.reset(new Locker{isolate});
            defaultZclAttribute = std::make_unique<ZCLAttributeMock>();
            zclAttributeMock = std::make_unique<ZCLAttributeMock>();
            jsZCluster = make_unique<JSZCluster>(&jsZAttributeFactory, &singletonObjectsMock);
            extAddress = convertFromString(EXTENDED_ADDRESS);
            getAttribute = NAMED_ALLOW_CALL(cluster, getAttribute(ANY(int))).RETURN(defaultZclAttribute.get());
        }

        void JSZClusterTest::TearDown() {
            getZDevices.release();
            getClusters.release();
            zDeviceExists.release();
            getAttribute.release();
            jsZCluster.reset();
            locker.reset();
            isolate->Exit();
            isolate->Dispose();

            defaultZclAttribute.reset();
        }

        v8::Local<v8::Value> JSZClusterTest::runScript(const std::string &script) {
            std::cout << "script: " << script << std::endl;
            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            return jsScript->Run();
        }

        ExtAddress JSZClusterTest::convertFromString(const std::string &strExt) {
            ExtAddress extAddress{};
            std::stringstream stream{strExt};
            stream >> extAddress;
            return extAddress;
        }

        TEST_F(JSZClusterTest, createTemplate) {
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);

            Handle<Object> global = context->Global();
            jsZCluster->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSZClusterTest, createIstance) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);


            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_EQ(toString(object->GetConstructorName()), JSZCLUSTER);
        }

        TEST_F(JSZClusterTest, getAProperty) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << ");a.getProperyById(" << ATTRIBUTE1_ID <<
            ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);
            Local<Object> expectedObject = Object::New(isolate);

//            REQUIRE_CALL(jsZAttributeFactory, createAttributeInstance(_, _)).RETURN(Object::New(isolate));

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);
            REQUIRE_CALL(cluster, getAttribute(ATTRIBUTE1_ID)).RETURN(zclAttributeMock.get());
            REQUIRE_CALL(jsZAttributeFactory, createAttributeInstance(isolate, zclAttributeMock.get())).RETURN(expectedObject);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsObject(), true);

            Local<Object> resultObject = result->ToObject();

            ASSERT_EQ(resultObject->GetIdentityHash(), expectedObject->GetIdentityHash());
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihNoAttributes) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND0_ID << ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);
            REQUIRE_CALL(cluster, executeCommand(COMAND0_ID, _));
            REQUIRE_CALL(cluster, getCmdParams(COMAND0_ID)).RETURN(std::vector<ClusterCmdParamsBase *> {});

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUndefined(), true);
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihAttributes) {
            auto argUINT16 = make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("ARG U16");
            auto argString = make_unique<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("ARG STRING");

            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND1_ID << "," << COMAND1_ARG0 << ",'" << COMAND1_ARG1 << "');";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);

            REQUIRE_CALL(cluster, executeCommand(COMAND1_ID,dataIsFormedBy(COMAND1_ARG0, COMAND1_ARG1)));

            REQUIRE_CALL(cluster, getCmdParams(COMAND1_ID)).LR_RETURN(std::vector<ClusterCmdParamsBase *> {argUINT16.get(), argString.get()});

            v8::Local<v8::Value> result = runScript(stream.str());
            String::Utf8Value strResult(result);
            ASSERT_EQ(result.IsEmpty(), false)<< stream.str() << "=" << (*strResult);
            ASSERT_EQ(result->IsUndefined(), true);
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihAttributesAsUINT16_list) {
            auto argList = std::make_unique<ClusterCmdListParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group List");

            uint16_t data1 = 20;
            uint16_t data2 = 55;
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND2_ID << ",[" << data1 << "," << data2 << "]);";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);

            REQUIRE_CALL(cluster, executeCommand(COMAND2_ID,dataIsFormedBy(data1, data2)));
            auto cmdParams = std::vector<ClusterCmdParamsBase *> {argList.get()};
            REQUIRE_CALL(cluster, getCmdParams(COMAND2_ID)).RETURN(cmdParams);

            v8::Local<v8::Value> result = runScript(stream.str());
            String::Utf8Value strResult(result);
            ASSERT_EQ(result.IsEmpty(), false)<< stream.str() << "=" << (*strResult);
            ASSERT_EQ(result->IsUndefined(), true);
        }

    } /* namespace test */
} /* namespace zigbee */
