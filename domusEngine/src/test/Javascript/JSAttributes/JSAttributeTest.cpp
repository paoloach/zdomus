/*
 * JSAttributeTest.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#include <zcl/ZCLAttribute.h>
#include "JSAttributeTest.h"
#include "../../../JavaScript/JSZAttribute.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;


        auto inline toString(Local<String> arg) {
            v8::String::Utf8Value utf8Value(arg);
            return std::string(*utf8Value);
        }

        std::map<ZCLAttribute::Status, std::string> expectedStatusMap{{ZCLAttribute::Available,    "available"},
                                                                      {ZCLAttribute::NotAvailable, "notAvailable"},
                                                                      {
                                                                       ZCLAttribute::NotSupported, "notSupported"},
                                                                      {ZCLAttribute::Requesting,   "requesting"},
                                                                      {ZCLAttribute::Undefined,    "undefined"},};


        void JSAttributeTest::createTemplateTest(JSZAttribute *jsZAttribute) {
            HandleScope handle_scope(isolate);
            Local<Context> context = Context::New(isolate, nullptr);
            Context::Scope context_scope(context);

            Handle<Object> global = context->Global();
            jsZAttribute->initJsObjectsTemplate(isolate, global);
        }

        void JSAttributeTest::createIstanceTest(const std::string &attributeName, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream stream{};
            stream << attributeName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << "," << ATTRIBUTE0_ID << ");";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            REQUIRE_CALL(*zDevices, exists(extAddress)).RETURN(true);
            REQUIRE_CALL(*zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);

            REQUIRE_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).LR_RETURN(&cluster);
            REQUIRE_CALL(cluster, getAttribute(ATTRIBUTE0_ID)).RETURN(attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());

            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_EQ(toString(object->GetConstructorName()),attributeName);
        }

        ZDevice JSAttributeTest::createZDevice() {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            return ZDevice {extAddress, NWK_ADDRESS, 0, {zEndpoint}};
        }

        void JSAttributeTest::setInitExpectation(ZDevice &zDevice, ZCLAttribute * attributeMock) {
            exists = NAMED_REQUIRE_CALL(*zDevices, exists(extAddress)).RETURN(true);
            getDevice = NAMED_REQUIRE_CALL(*zDevices, getDevice(extAddress)).LR_RETURN(&zDevice);
            getCluster = NAMED_REQUIRE_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).RETURN(&cluster);
            getAttribute = NAMED_REQUIRE_CALL(cluster, getAttribute(ATTRIBUTE0_ID)).RETURN(attributeMock);
        }

        void JSAttributeTest::isAvailableTest(bool availableStatus, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isAvailable();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_EQ(result->BooleanValue(), availableStatus);
        }

        void JSAttributeTest::isUnsupportedTest(bool availableStatus, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isUnsupported();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_EQ(result->BooleanValue(), availableStatus);
        }

        void JSAttributeTest::getStatusTest(ZCLAttribute::Status statusExpected, JSZAttribute *jsZAttribute,
                                            ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.getStatus();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsString(), true);
            String::Utf8Value status(result);
            std::string expectedStatusValue = expectedStatusMap[statusExpected];
            ASSERT_EQ(*status, expectedStatusValue);
        }

        void JSAttributeTest::getIdentifierTest(JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.getIdentifier();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUint32(), true);
            ASSERT_EQ(result->Uint32Value(), ATTRIBUTE0_ID);
        }

        void JSAttributeTest::getNameTest(const std::string &expectedName, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.getName();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsString(), true);
            String::Utf8Value name(result);
            ASSERT_EQ(*name, expectedName);
        }

        void JSAttributeTest::isReadonlyTest(bool readOnlyExpected, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isReadOnly();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsBoolean(), true);
            ASSERT_EQ(result->BooleanValue(), readOnlyExpected);
        }

        std::string JSAttributeTest::createZAttributeVariable(const std::string &attributeName) {
            std::stringstream stream{};
            stream << "var a=" << attributeName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << "," << ATTRIBUTE0_ID << ");";
            return stream.str();
        }

    } /* namespace test */
} /* namespace zigbee */
