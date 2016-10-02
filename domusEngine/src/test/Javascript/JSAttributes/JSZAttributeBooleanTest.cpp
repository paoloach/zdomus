/*
 * JSZAttributeBooleanTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeBooleanTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttributeBooleanTest::~JSZAttributeBooleanTest() {
        }

        void JSZAttributeBooleanTest::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeBool>(zDevices.get(), zigbeeDevice, clusterTypeFactoryMock);
            zcl_boolean_AttributeMock = std::make_shared<ZCL_boolean_AttributeMock>();
            zAttributeVariable = createZAttributeVariable("Z" + ZCL_boolean_Attribute::name());
            EXPECT_CALL(*zcl_boolean_AttributeMock, getZCLType()).Times(AnyNumber()).WillOnce(
                    Return(ZCLTypeDataType::ZCLTypeBool));
        }

        void JSZAttributeBooleanTest::TearDown() {
            jsZAttribute.reset();
            zcl_boolean_AttributeMock.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeBooleanTest, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeBooleanTest, createIstance) {
            createIstanceTest("Z" + ZCL_boolean_Attribute::name(), jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getValue) {
            bool expectedValue = true;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_boolean_AttributeMock);
            EXPECT_CALL(*zcl_boolean_AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsBoolean(), true);
            bool value = result->BooleanValue();

            ASSERT_THAT(value, Eq(expectedValue));
        }

        TEST_F(JSZAttributeBooleanTest, setValue) {
            bool expectedValue = false;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=false;";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_boolean_AttributeMock);
            EXPECT_CALL(*zcl_boolean_AttributeMock, sendValue(expectedValue));

            runScript(stream.str());
        }

        TEST_F(JSZAttributeBooleanTest, setWrongValue) {
            int16_t expectedValue = -15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_boolean_AttributeMock);

            TryCatch trycatch;
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), true);
            ASSERT_THAT(trycatch.HasCaught(), true);
            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));

        }

        TEST_F(JSZAttributeBooleanTest, requestValue) {
            EXPECT_CALL(*zcl_boolean_AttributeMock, requestValue());
            requestValueTest(jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(*zcl_boolean_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(*zcl_boolean_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(*zcl_boolean_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(*zcl_boolean_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(*zcl_boolean_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getIdentifier) {
            EXPECT_CALL(*zcl_boolean_AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(*zcl_boolean_AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_boolean_AttributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(*zcl_boolean_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_boolean_AttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
