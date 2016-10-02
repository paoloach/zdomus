/*
 * JSZAttributeUInt24Test.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeUInt24Test.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        JSZAttributeUInt24Test::~JSZAttributeUInt24Test() {
        }

        void JSZAttributeUInt24Test::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeUint24>(zDevices.get(), zigbeeDevice, clusterTypeFactoryMock);
            zclUInt24AttributeMock = std::make_shared<ZCLUInt24AttributeMock>();
            zAttributeVariable = createZAttributeVariable("Z" + ZCLUInt24AttributeMock::name());
            EXPECT_CALL(*zclUInt24AttributeMock, getZCLType()).Times(AnyNumber()).WillOnce(
                    Return(ZCLTypeDataType::ZCLTypeUInt24));
        }

        void JSZAttributeUInt24Test::TearDown() {
            jsZAttribute.reset();
            zclUInt24AttributeMock.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeUInt24Test, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeUInt24Test, createIstance) {
            createIstanceTest("Z" + ZCLUInt24AttributeMock::name(), jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, getValue) {
            uint32_t expectedValue = 13;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zclUInt24AttributeMock);
            EXPECT_CALL(*zclUInt24AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            uint32_t value = result->ToUint32()->Value();

            ASSERT_THAT(value, Eq(expectedValue));
        }

        TEST_F(JSZAttributeUInt24Test, setValue) {
            uint32_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zclUInt24AttributeMock);
            EXPECT_CALL(*zclUInt24AttributeMock, sendValue(expectedValue));

            runScript(stream.str());
        }

        TEST_F(JSZAttributeUInt24Test, setWrongValue) {
            int16_t expectedValue = -15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, zclUInt24AttributeMock);

            TryCatch trycatch;
            v8::Local<v8::Value> result = runScript(stream.str());
            ASSERT_THAT(result.IsEmpty(), true);
            ASSERT_THAT(trycatch.HasCaught(), true);
            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));
        }

        TEST_F(JSZAttributeUInt24Test, requestValue) {
            EXPECT_CALL(*zclUInt24AttributeMock, requestValue());
            requestValueTest(jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(*zclUInt24AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(*zclUInt24AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(*zclUInt24AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(*zclUInt24AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(*zclUInt24AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(*zclUInt24AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(*zclUInt24AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(*zclUInt24AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(*zclUInt24AttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, getIdentifier) {
            EXPECT_CALL(*zclUInt24AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(*zclUInt24AttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(*zclUInt24AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zclUInt24AttributeMock);
        }

        TEST_F(JSZAttributeUInt24Test, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(*zclUInt24AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, zclUInt24AttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
