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

        std::map<ZCLAttribute::Status, std::string> expectedStatusMap{{ZCLAttribute::Available,    "available"},
                                                                      {ZCLAttribute::NotAvailable, "notAvailable"},
                                                                      {
                                                                       ZCLAttribute::NotSupported, "notSupported"},
                                                                      {ZCLAttribute::Requesting,   "requesting"},
                                                                      {ZCLAttribute::Undefined,    "undefined"},};

        JSAttributeTest::~JSAttributeTest() {
        }

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

            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));

            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(&cluster));
            EXPECT_CALL(cluster, getAttribute(ATTRIBUTE0_ID)).WillOnce(Return(attributeMock));

            v8::Local<v8::Value> result = runScript(stream.str());

            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsObject(), true);
            Local<Object> object = result->ToObject();

            ASSERT_THAT(object->GetConstructorName(), IsString(attributeName));
        }

        ZDevice JSAttributeTest::createZDevice() {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            return ZDevice {extAddress, NWK_ADDRESS, 0, {zEndpoint}};
        }

        void JSAttributeTest::setInitExpectation(ZDevice &zDevice, ZCLAttribute * attributeMock) {
            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, CLUSTER_ID)).WillOnce(Return(&cluster));
            EXPECT_CALL(cluster, getAttribute(ATTRIBUTE0_ID)).WillOnce(Return(attributeMock));
        }

        void JSAttributeTest::isAvailableTest(bool availableStatus, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isAvailable();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsBoolean(), true);
            ASSERT_THAT(result->BooleanValue(), availableStatus);
        }

        void JSAttributeTest::isUnsupportedTest(bool availableStatus, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isUnsupported();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsBoolean(), true);
            ASSERT_THAT(result->BooleanValue(), availableStatus);
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
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsString(), true);
            String::Utf8Value status(result);
            std::string expectedStatusValue = expectedStatusMap[statusExpected];
            ASSERT_THAT(*status, StrEq(expectedStatusValue));
        }

        void JSAttributeTest::getIdentifierTest(JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.getIdentifier();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            ASSERT_THAT(result->Uint32Value(), Eq(ATTRIBUTE0_ID));
        }

        void JSAttributeTest::getNameTest(const std::string &expectedName, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.getName();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsString(), true);
            String::Utf8Value name(result);
            ASSERT_THAT(*name, StrEq(expectedName));
        }

        void JSAttributeTest::isReadonlyTest(bool readOnlyExpected, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.isReadOnly();";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, attributeMock);

            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsBoolean(), true);
            ASSERT_THAT(result->BooleanValue(), Eq(readOnlyExpected));
        }

        std::string JSAttributeTest::createZAttributeVariable(const std::string &attributeName) {
            std::stringstream stream{};
            stream << "var a=" << attributeName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << CLUSTER_ID << "," << ATTRIBUTE0_ID << ");";
            return stream.str();
        }

    } /* namespace test */
} /* namespace zigbee */
