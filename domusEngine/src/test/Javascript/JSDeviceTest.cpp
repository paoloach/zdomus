/*
 * JSDeviceTest.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include "JSDeviceTest.h"
#include "../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using trompeloeil::_;


        inline auto getConstructorName(Local<Object> & object){
            String::Utf8Value utf8Message(object->GetConstructorName());
            return std::string(*utf8Message);
        }

        inline auto toString(Local<String> & v8String){
            String::Utf8Value utf8Message(v8String);
            return std::string(*utf8Message);
        }

#define V8_SETUP HandleScope handle_scope(isolate);\
                Local<Context> context = Context::New(isolate, nullptr);\
                Context::Scope context_scope(context);\
                Local<Object>  global = context->Global(); \
                jsDevice->initJsObjectsTemplate(isolate,global);

        static std::string extendedAddress = "00-01-02-03-04-05-06-07";
        static GenericMessage annunceMsg1{1};
        static GenericMessage simpleeMsg{2};
        static AnnunceMessage annunce1{annunceMsg1, 2, {3, 4, 5, 6, 7, 8, 9, 10}, 11};
        static AnnunceMessage annuncePanOn{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x01};
        static AnnunceMessage annunceFullFunctionalOn{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x02};
        static AnnunceMessage annunceMainPowerSourcedOn{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x04};
        static AnnunceMessage annunceRFOnIdleOn{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x08};
        static AnnunceMessage annunceSecureCapableOn{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x40};
        static AnnunceMessage annunceAllOff{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 0x00};

        class CheckEmptyPersistentHandleVisitor : public PersistentHandleVisitor {
            virtual void VisitPersistentHandle(Persistent<v8::Value> *, uint16_t) override {
            }
        };

        void JSDeviceTest::getJSDevice(const v8::FunctionCallbackInfo<v8::Value> &info) {
            JSDeviceTest *This = (JSDeviceTest *) Local<External>::Cast(info.Data())->Value();

            v8::String::Utf8Value extAddressString(info[0]);
            std::stringstream stream{*extAddressString};
            ExtAddress extAddress{};
            stream >> extAddress;
            info.GetReturnValue().Set(This->jsDevice->createInstance(This->isolate, extAddress));
        }

        void JSDeviceTest::SetUp() {
            zDevices = std::make_unique<ZDevicesMock>();
            creatingZDeviceScript = "var a = " + std::string(JSZDEVICE) + "('" + extendedAddress + "');";

            std::stringstream stream{extendedAddress};
            stream >> extAddress;
            auto zDevicesP = zDevices.get();
            jsDevice = std::make_unique<JSZDevice>(zDevicesP, &jsEndpoint);
            createParams.array_buffer_allocator = &v8Allocator;
            isolate = v8::Isolate::New(createParams);
            isolate->Enter();
            locker.reset(new Locker{isolate});
            ALLOW_CALL(jsEndpoint, createInstance(_, _, _)).RETURN(Local<Object>());
        }

        void JSDeviceTest::TearDown() {
            locker.reset();
            isolate->Exit();
         //   V8::VisitHandlesWithClassIds(isolate, new CheckEmptyPersistentHandleVisitor{});
            jsDevice.reset();

            isolate->Dispose();
            zDevices.reset();
        }

        v8::Local<v8::Value> JSDeviceTest::runScript(const std::string &script) {
            Local<String> source = String::NewFromUtf8(isolate, script.c_str());
            Local<Script> jsScript = Script::Compile(source);
            return jsScript->Run();
        }

        TEST_F(JSDeviceTest, createTemplate) {
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);
            Handle<Object> global = context->Global();
            jsDevice->initJsObjectsTemplate(isolate, global);
        }

        TEST_F(JSDeviceTest, createIstance) {
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a;");
            String::Utf8Value utf8(result);
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_EQ(getConstructorName(object),JSZDEVICE);
        }

        TEST_F(JSDeviceTest, createInvalidIstance) {
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(false);

            TryCatch trycatch{};
            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a;");
            String::Utf8Value utf8(result);
            ASSERT_EQ(result.IsEmpty(), true);
            ASSERT_EQ(trycatch.HasCaught(), true);

        }

        TEST_F(JSDeviceTest, getExtendedAddress) {
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.longAddress");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsString(), true);
            v8::Local<String> JSExtendedAddress = Local<String>::Cast(result);
            ASSERT_EQ(toString(JSExtendedAddress), extendedAddress);
        }

        TEST_F(JSDeviceTest, getShortAddress) {
            ZDevice zDevice{annunce1};
            V8_SETUP

            REQUIRE_CALL(*zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.shortAddress");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsInt32(), true);
            v8::Local<Integer> JSShortAddress = Local<Integer>::Cast(result);
            ASSERT_EQ(JSShortAddress->Value(), zDevice.getNwkAddr().getId());
        }

        TEST_F(JSDeviceTest, isPanCapable) {
            ZDevice zDevice{annuncePanOn};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isPan();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_TRUE(result->ToBoolean()->Value());
        }

        TEST_F(JSDeviceTest, isNotPan) {
            ZDevice zDevice{annunceAllOff};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isPan();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_FALSE(result->ToBoolean()->Value());
        }

        TEST_F(JSDeviceTest, isFullFunctionalNode) {
            ZDevice zDevice{annunceFullFunctionalOn};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isFullFunctionDevice();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_TRUE(result->ToBoolean()->Value());
        }

        TEST_F(JSDeviceTest, isNotFullFunctionalNode) {
            ZDevice zDevice{annunceAllOff};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isFullFunctionDevice();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_FALSE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isMainPowerSurced) {
            ZDevice zDevice{annunceMainPowerSourcedOn};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isMainPoweredSource();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_TRUE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isNotMainPowerSurced) {
            ZDevice zDevice{annunceAllOff};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isMainPoweredSource();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_FALSE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isReceiverOnWhenIdle) {
            ZDevice zDevice{annunceRFOnIdleOn};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isDisableRFInIDLE();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_TRUE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isReceiverOffWhenIdle) {
            ZDevice zDevice{annunceAllOff};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isDisableRFInIDLE();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_FALSE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isSecureCapable) {
            ZDevice zDevice{annunceSecureCapableOn};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isSecureCapable();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_TRUE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, isNotSecureCapable) {
            ZDevice zDevice{annunceAllOff};
            V8_SETUP

            REQUIRE_CALL(*zDevices.get(), exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices.get(), getDevice(extAddress)).LR_RETURN(&zDevice);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.isSecureCapable();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_FALSE(result->BooleanValue());
        }

        TEST_F(JSDeviceTest, getEndpoints) {
            EndpointID endpointId1{20};
            EndpointID endpointId2{21};
            ZEndpoint endpoint1{NwkAddr {1}, endpointId1, 30, 31, 32, {ClusterID {50}}, {ClusterID {51}}};
            ZEndpoint endpoint2{NwkAddr {1}, endpointId2, 30, 31, 32, {ClusterID {60}}, {ClusterID {61}}};
            ZDevice zDevice{extAddress, NwkAddr(1), 0, {endpoint1, endpoint2}};
            V8_SETUP

            Local<Object> objectEndpoint1 = Object::New(isolate);
            Local<Object> objectEndpoint2 = Object::New(isolate);

            REQUIRE_CALL(*zDevices, exists(extAddress)).RETURN(true);

            REQUIRE_CALL(*zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            REQUIRE_CALL(jsEndpoint, createInstance(isolate, extAddress, endpointId1)).RETURN(objectEndpoint1);
            REQUIRE_CALL(jsEndpoint, createInstance(isolate, extAddress, endpointId2)).RETURN(objectEndpoint2);

            v8::Local<v8::Value> result = runScript(creatingZDeviceScript + "a.getEndpoints();");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsArray(), true);
            Local<Array> array = result.As<Array>();

            ASSERT_EQ(array->Length(), 2);
            ASSERT_EQ(array->Get(0)->IsObject(), true);
            ASSERT_EQ(array->Get(1)->IsObject(), true);
            Local<Object> jszEndpoint0 = array->Get(0).As<Object>();
            Local<Object> jszEndpoint1 = array->Get(1).As<Object>();
            ASSERT_EQ(jszEndpoint0->GetIdentityHash(), objectEndpoint1->GetIdentityHash());
            ASSERT_EQ(jszEndpoint1->GetIdentityHash(), objectEndpoint2->GetIdentityHash());
        }

    } /* namespace test */
} /* namespace zigbee */
