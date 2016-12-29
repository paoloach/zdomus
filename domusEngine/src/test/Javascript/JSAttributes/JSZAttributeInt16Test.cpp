/*
 * JSZAttributeInt16Test.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeInt16Test.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttributeInt16Test::~JSZAttributeInt16Test() {
        }

        void JSZAttributeInt16Test::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeInt16>(&singletonObjectsMock, fifo);
            zcl_int16_AttributeMock = std::make_shared<ZCL_int16_AttributeMock>();
            zAttributeVariable = createZAttributeVariable("Z" + ZCL_int16_Attribute::name());
            EXPECT_CALL(*zcl_int16_AttributeMock, getZCLType()).Times(AnyNumber()).WillOnce(
                    Return(ZCLTypeDataType::ZCLTypeSInt16));
        }

        void JSZAttributeInt16Test::TearDown() {
            jsZAttribute.reset();
            zcl_int16_AttributeMock.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeInt16Test, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeInt16Test, createIstance) {
            createIstanceTest("Z" + ZCL_int16_Attribute::name(), jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, getValue) {
            auto expectedValue = 13;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_int16_AttributeMock);
            EXPECT_CALL(*zcl_int16_AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");

            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsInt32(), true);
            ASSERT_THAT(result->Int32Value(), Eq(expectedValue));
        }

        TEST_F(JSZAttributeInt16Test, setPositiveValue) {
            int16_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_int16_AttributeMock);
            EXPECT_CALL(*zcl_int16_AttributeMock, sendValue(expectedValue));

            runScript(stream.str());
        }

        TEST_F(JSZAttributeInt16Test, setNegativeValue) {
            int16_t expectedValue = -15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_int16_AttributeMock);
            EXPECT_CALL(*zcl_int16_AttributeMock, sendValue(expectedValue));

            runScript(stream.str());

        }

        TEST_F(JSZAttributeInt16Test, requestValue) {
            EXPECT_CALL(*zcl_int16_AttributeMock, requestValue());
            requestValueTest(jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(*zcl_int16_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(*zcl_int16_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(*zcl_int16_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(*zcl_int16_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(*zcl_int16_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(*zcl_int16_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(*zcl_int16_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(*zcl_int16_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(*zcl_int16_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, getIdentifier) {
            EXPECT_CALL(*zcl_int16_AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(*zcl_int16_AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(*zcl_int16_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_int16_AttributeMock);
        }

        TEST_F(JSZAttributeInt16Test, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(*zcl_int16_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_int16_AttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
