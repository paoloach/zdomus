/*
 * JSZAttributeUInt8Test.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeUInt8Test.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttributeUInt8Test::~JSZAttributeUInt8Test() {
        }

        void JSZAttributeUInt8Test::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeUint8>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLUint8AttributeMock::name());
        }

        void JSZAttributeUInt8Test::TearDown() {
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeUInt8Test, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeUInt8Test, createInstance) {

            createIstanceTest("Z" + ZCLUint8AttributeMock::name(), jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getValue) {
            auto expectedValue = 13u;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &zclUint8AttributeMock);
            EXPECT_CALL(zclUint8AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);

            ASSERT_THAT(result->ToUint32()->Value(), Eq(expectedValue));
        }

        TEST_F(JSZAttributeUInt8Test, setValue) {
            uint8_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << (uint32_t) expectedValue << ";";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &zclUint8AttributeMock);

            runScript(stream.str());
        }

//        TEST_F(JSZAttributeUInt8Test, setWrongValue) {
//            int16_t expectedValue = -15;
//            ZDevice zDevice{createZDevice()};
//            std::stringstream stream{};
//            stream << zAttributeVariable << "a.value=" << expectedValue;
//            V8_SETUP
//            jsZAttribute->initJsObjectsTemplate(isolate, global);
//
//            setInitExpectation(zDevice, &zclUint8AttributeMock);
//
//            TryCatch trycatch;
//            v8::Local<v8::Value> result = runScript(stream.str());
//            ASSERT_THAT(result.IsEmpty(), true);
//            ASSERT_THAT(trycatch.HasCaught(), true);
//            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
//            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));
//
//        }

        TEST_F(JSZAttributeUInt8Test, requestValue) {
            EXPECT_CALL(zclUint8AttributeMock, requestValue());
            requestValueTest(jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(zclUint8AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(zclUint8AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(zclUint8AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(zclUint8AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(zclUint8AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(zclUint8AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(zclUint8AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(zclUint8AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(zclUint8AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getIdentifier) {
            EXPECT_CALL(zclUint8AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(zclUint8AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(zclUint8AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclUint8AttributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(zclUint8AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclUint8AttributeMock);
        }

    } /* namespace test */
} /* namespace zigbee */
