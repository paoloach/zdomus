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
            jsZAttribute = std::make_unique<JSZAttributeUint8>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLuint8Attribute::name());
            zclTypeExpectation = NAMED_ALLOW_CALL(attributeMock,getZCLType()).RETURN(ZCLTypeDataType::ZCLTypeUInt8);
        }

        void JSZAttributeUInt8Test::TearDown() {
            zclTypeExpectation.reset();
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeUInt8Test, createTemplate) {
            createTemplateTest(jsZAttribute.get());
        }

        TEST_F(JSZAttributeUInt8Test, createInstance) {

            createIstanceTest("Z" + ZCLuint8Attribute::name(), jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getValue) {
            auto expectedValue = 13u;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);
            REQUIRE_CALL(attributeMock, getValue()).RETURN(std::any(expectedValue));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsUint32(), true);

            ASSERT_EQ(result->ToUint32()->Value(), expectedValue);
        }

        TEST_F(JSZAttributeUInt8Test, setValue) {
            uint8_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << (uint32_t) expectedValue << ";";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);

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
//            ASSERT_EQ(result.IsEmpty(), true);
//            ASSERT_EQ(trycatch.HasCaught(), true);
//            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
//            ASSERT_EQ(*exceptionMessage, HasSubstr("Invalid parameter"));
//
//        }

        TEST_F(JSZAttributeUInt8Test, isAvailable) {
            bool availableStatus = true;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isNotAvailable) {
            bool availableStatus = false;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isUnsupported) {
            bool unsupported = true;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isSupported) {
            bool unsupported = false;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getIdentifier) {
            REQUIRE_CALL(attributeMock, getIdentifier()).RETURN(ATTRIBUTE0_ID);
            getIdentifierTest(jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, getName) {
            std::string expectedName = "name";
            REQUIRE_CALL(attributeMock, getName()).RETURN(expectedName);
            getNameTest(expectedName, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isReadOnly) {
            bool readOnlyValue = true;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt8Test, isWritable) {
            bool readOnlyValue = false;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

    } /* namespace test */
} /* namespace zigbee */
