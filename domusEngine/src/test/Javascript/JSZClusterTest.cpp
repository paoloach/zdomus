/*
 * JSZClusterTest.cpp
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZClusterTest.h"

#include "../../JavaScript/JSObjects.h"
#include "../Mocks/ClusterMock.h"
#include "ClusterCmdArgumentMatcher.h"
#include "ClusterCmdArrayArgumentMatcher.h"
#include <sstream>

namespace zigbee {

    std::ostream  & operator<<(std::ostream & out,  ZCLAttribute *  attribute){
        out << "attribute" << attribute->getName();
        return out;
    }

    namespace test {

        using std::make_unique;
        using std::make_shared;
        using namespace v8;
        using namespace testing;

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

        class TestCluster1 : public ClusterMock {
        public:
            virtual ~TestCluster1() =default;
            TestCluster1(ZigbeeDevice * zigbeeDevice, EndpointID endpoint, NwkAddr networkAddress,
                         const std::shared_ptr<ClusterCmdParamsBase> &cmdParam1,
                         const std::shared_ptr<ClusterCmdParamsBase> &cmdParam2, const std::shared_ptr<ClusterCmdParamsBase> &cmdParam3) :
                    ClusterMock(zigbeeDevice, endpoint, networkAddress) {

                std::copy(ATTRIBUTES_DEF.begin(), ATTRIBUTES_DEF.end(), std::back_inserter(_attributesDef));

                _commandsDef.emplace_back([this](std::vector<uint8_t> ){this->comand1Executed++;}, COMAND0_ID, "Comand 1");
                _commandsDef.emplace_back([this](std::vector<uint8_t> ){this->comand2Executed++;}, COMAND1_ID, "Comand 2", cmdParam1, cmdParam2);
                _commandsDef.emplace_back([](std::vector<uint8_t> ){}, COMAND2_ID, "Comand 3", cmdParam3);

                comand1Executed = 0;
                comand2Executed = 0;
            }


            int comand1Executed;
            int comand2Executed;
        };


        void JSZClusterTest::SetUp() {
            ON_CALL(singletonObjectsMock, getZDevices()).WillByDefault(Return(&zDevices));
            ON_CALL(singletonObjectsMock, getClusters()).WillByDefault(Return(&clusters));
            ON_CALL(zDevices, exists(_)).WillByDefault(Return(false));

            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
            isolate->Enter();
            locker.reset(new Locker{isolate});
            defaultCluster = std::make_shared<ClusterMock>(&zigbeeDevice, ENDPOINT_ID, NWK_ADDRESS);
            defaultZclAttribute = std::make_shared<ZCLAttributeMock>(&zigbeeDevice, defaultCluster.get(), -1, ZCLTypeDataType::ZCLTypeInvalid, "", true);
            cluster = std::make_shared<TestCluster1>(&zigbeeDevice, ENDPOINT_ID, NWK_ADDRESS, COMAND_PARAM_UINT16, COMAND_PARAM_STRING, COMAND_PARAM_LIST_UINT16);
            zclAttributeMock = std::make_shared<ZCLAttributeMock>(&zigbeeDevice, cluster.get(), ATTRIBUTE1_ID, ZCLTypeDataType::ZCLTypeUInt16, ATTRIBUTE1_NAME, true);
            zclAttribute = std::dynamic_pointer_cast<ZCLAttribute>(zclAttributeMock);

            jsZCluster = make_unique<JSZCluster>(&jsZAttributeFactory, &singletonObjectsMock);
            extAddress = convertFromString(EXTENDED_ADDRESS);
            ON_CALL(*cluster, getAttribute(A<int>())).WillByDefault(Return(defaultZclAttribute));
        }

        void JSZClusterTest::TearDown() {
            jsZCluster.reset();
            locker.reset();
            isolate->Exit();
            isolate->Dispose();

            defaultZclAttribute.reset();
            defaultCluster.reset();
            cluster.reset();
        }

        v8::Local<v8::Value> JSZClusterTest::runScript(const std::string &script) {
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
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            HandleScope handle_scope(isolate);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            Local<Context> context = Context::New(isolate, nullptr);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            Context::Scope context_scope(context);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            Handle<Object> global = context->Global();
            jsZCluster->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSZClusterTest, createIstance) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ", " << CLUSTER_ID << ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(cluster));


            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_THAT(object->GetConstructorName(), IsString(JSZCLUSTER));
        }

        TEST_F(JSZClusterTest, getAProperty) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ", " << CLUSTER_ID << ");a.getProperyById(" << ATTRIBUTE1_ID <<
            ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);
            Local<Object> expectedObject = Object::New(isolate);

            ON_CALL(jsZAttributeFactory, createAttributeInstance(_, _)).WillByDefault(Return(Object::New(isolate)));

            std::shared_ptr<Cluster> clusterReal  = cluster;

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(cluster));
            EXPECT_CALL(*cluster, getAttribute(ATTRIBUTE1_ID)).WillOnce(Return(zclAttributeMock));
            EXPECT_CALL(jsZAttributeFactory, createAttributeInstance(isolate, zclAttribute)).WillOnce(Return(expectedObject));

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsObject(), true);

            Local<Object> resultObject = result->ToObject();

            ASSERT_THAT(resultObject->GetIdentityHash(), Eq(expectedObject->GetIdentityHash()));
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihNoAttributes) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND0_ID << ");";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(cluster));
            EXPECT_CALL(*cluster, executeComand(COMAND0_ID, _));
            EXPECT_CALL(*cluster, getCmdParams(COMAND0_ID)).WillOnce(Return(std::vector<std::shared_ptr<ClusterCmdParamsBase>> {}));

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUndefined(), true);
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihAttributes) {
            auto argUINT16 = make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("ARG U16");
            auto argString = make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("ARG STRING");

            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND1_ID << "," << COMAND1_ARG0 << ",'" << COMAND1_ARG1 << "');";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(cluster));
            EXPECT_CALL(*cluster, executeComand(COMAND1_ID,
                                                HasArgument<uint16_t, const char *, ZCLTypeDataType::ZCLTypeUInt16, ZCLTypeDataType::ZCLTypeStringChar>(COMAND1_ARG0,
                                                                                                                                                        COMAND1_ARG1)));
            EXPECT_CALL(*cluster, getCmdParams(COMAND1_ID)).WillOnce(Return(std::vector<std::shared_ptr<ClusterCmdParamsBase>> {argUINT16, argString}));

            v8::Local<v8::Value> result = runScript(stream.str());
            String::Utf8Value strResult(result);
            ASSERT_THAT(result.IsEmpty(), false)<< stream.str() << "=" << (*strResult);
            ASSERT_THAT(result->IsUndefined(), true);
        }

        TEST_F(JSZClusterTest, executeCmdByIdWihAttributesAsUINT16_list) {
            auto argList = std::make_shared<ClusterCmdListParams<ZCLTypeDataType::ZCLTypeUInt16>>("Group List");

            uint16_t data1 = 20;
            uint16_t data2 = 55;
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << "var a = " << JSZCLUSTER << "('" << EXTENDED_ADDRESS << "', " << ENDPOINT_ID << ", " << CLUSTER_ID << ");";
            stream << "a.executeCmdById(" << COMAND2_ID << ",[" << data1 << "," << data2 << "]);";
            V8_SETUP
            jsZCluster->initJsObjectsTemplate(isolate, global);

            EXPECT_CALL(zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clusters, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(cluster));

            EXPECT_CALL(*cluster, executeComand(COMAND2_ID, HasArraysArgument<uint16_t, ZCLTypeDataType::ZCLTypeUInt16>({data1, data2})));
            EXPECT_CALL(*cluster, getCmdParams(COMAND2_ID)).WillOnce(Return(std::vector<std::shared_ptr<ClusterCmdParamsBase>> {argList}));

            v8::Local<v8::Value> result = runScript(stream.str());
            String::Utf8Value strResult(result);
            ASSERT_THAT(result.IsEmpty(), false)<< stream.str() << "=" << (*strResult);
            ASSERT_THAT(result->IsUndefined(), true);
        }

    } /* namespace test */
} /* namespace zigbee */
