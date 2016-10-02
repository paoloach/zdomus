/*
 * JSZAttributeStringTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeStringTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttributeStringTest::~JSZAttributeStringTest() {

        }

        void JSZAttributeStringTest::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeString>(zDevices.get(), zigbeeDevice, clusterTypeFactoryMock);
            zcl_string_AttributeMock = std::make_shared<ZCL_string_AttributeMock>();
            zAttributeVariable = createZAttributeVariable("Z" + ZCL_string_Attribute::name());
            EXPECT_CALL(*zcl_string_AttributeMock, getZCLType()).Times(AnyNumber()).WillOnce(
                    Return(ZCLTypeDataType::ZCLTypeStringChar));
        }

        void JSZAttributeStringTest::TearDown() {
            jsZAttribute.reset();
            zcl_string_AttributeMock.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeStringTest, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeStringTest, createIstance) {
            createIstanceTest("Z" + ZCL_string_Attribute::name(), jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, getValue) {
            std::string expectedValue = "a string";
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_string_AttributeMock);
            EXPECT_CALL(*zcl_string_AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsString(), true);
            String::Utf8Value value(result);
            ASSERT_THAT(*value, Eq(expectedValue));
        }

        TEST_F(JSZAttributeStringTest, setValue) {
            std::string expectedValue = "a string";
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value='" << expectedValue << "'";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_string_AttributeMock);
            EXPECT_CALL(*zcl_string_AttributeMock, sendValue(expectedValue));

            runScript(stream.str());
        }

        TEST_F(JSZAttributeStringTest, setWrongValue) {
            int16_t aNumber = -15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << aNumber;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_string_AttributeMock);

            TryCatch trycatch;
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), true);
            ASSERT_THAT(trycatch.HasCaught(), true);
            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));
        }

        TEST_F(JSZAttributeStringTest, requestValue) {
            EXPECT_CALL(*zcl_string_AttributeMock, requestValue());
            requestValueTest(jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(*zcl_string_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(*zcl_string_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(*zcl_string_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(*zcl_string_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(*zcl_string_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(*zcl_string_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(*zcl_string_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(*zcl_string_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(*zcl_string_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, getIdentifier) {
            EXPECT_CALL(*zcl_string_AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(*zcl_string_AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(*zcl_string_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_string_AttributeMock);
        }

        TEST_F(JSZAttributeStringTest, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(*zcl_string_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_string_AttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
