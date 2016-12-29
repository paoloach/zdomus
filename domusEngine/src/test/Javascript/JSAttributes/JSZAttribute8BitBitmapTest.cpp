/*
 * JSZAttribute8BitBitmapTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttribute8BitBitmapTest.h"

#include "JSZAttribute8BitBitmapTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttribute8BitBitmapTest::~JSZAttribute8BitBitmapTest() {
        }

        void JSZAttribute8BitBitmapTest::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttribute8BitBitmap>(&singletonObjectsMock, fifo);
            zcl_bitmap8bit_AttributeMock = std::make_shared<ZCL_bitmap8bit_AttributeMock>();
            zAttributeVariable = createZAttributeVariable("Z" + ZCL_bitmap8bit_Attribute::name());
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getZCLType()).Times(AnyNumber()).WillRepeatedly(
                    Return(ZCLTypeDataType::ZCLType8bitBitmap));
        }

        void JSZAttribute8BitBitmapTest::TearDown() {
            jsZAttribute.reset();
            zcl_bitmap8bit_AttributeMock.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttribute8BitBitmapTest, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttribute8BitBitmapTest, createIstance) {
            createIstanceTest("Z" + ZCL_bitmap8bit_Attribute::name(), jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getValue) {
            auto expectedValue = 13u;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_bitmap8bit_AttributeMock);
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            uint16_t value = result->ToUint32()->Value();

            ASSERT_THAT(value, Eq(expectedValue));
        }

        TEST_F(JSZAttribute8BitBitmapTest, setValue) {
            uint16_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_bitmap8bit_AttributeMock);
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, sendValue(expectedValue));

            runScript(stream.str());
        }

        TEST_F(JSZAttribute8BitBitmapTest, setWrongValue) {
            int16_t expectedValue = -15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zcl_bitmap8bit_AttributeMock);

            TryCatch trycatch;
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), true);
            ASSERT_THAT(trycatch.HasCaught(), true);
            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));

        }

        TEST_F(JSZAttribute8BitBitmapTest, requestValue) {
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, requestValue());
            requestValueTest(jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getIdentifier) {
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(*zcl_bitmap8bit_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zcl_bitmap8bit_AttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
