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
            jsZAttribute = std::make_unique<JSZAttributeBool>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLBooleanAttribute::name());
            zclTypeExpectation = NAMED_ALLOW_CALL(attributeMock,getZCLType()).RETURN(ZCLTypeDataType::ZCLTypeBool);
        }

        void JSZAttributeBooleanTest::TearDown() {
            zclTypeExpectation.reset();
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeBooleanTest, createTemplate) {
            createTemplateTest(jsZAttribute.get());
        }

        TEST_F(JSZAttributeBooleanTest, createIstance) {
            createIstanceTest("Z" + ZCLBooleanAttribute::name(), jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getValue) {
            bool expectedValue = true;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);
            REQUIRE_CALL(attributeMock, getValue()).RETURN(std::any(expectedValue));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsBoolean(), true);
            bool value = result->BooleanValue();

            ASSERT_THAT(value, Eq(expectedValue));
        }

        TEST_F(JSZAttributeBooleanTest, setValue) {
            ZDevice zDevice{createZDevice()};
            std::stringstream stream;
            stream << zAttributeVariable << "a.value=false;";
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);

            runScript(stream.str());
        }


        TEST_F(JSZAttributeBooleanTest, isAvailable) {
            bool availableStatus = true;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isNotAvailable) {
            bool availableStatus = false;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isUnsupported) {
            bool unsupported = true;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isSupported) {
            bool unsupported = false;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getIdentifier) {
            REQUIRE_CALL(attributeMock, getIdentifier()).RETURN(ATTRIBUTE0_ID);
            getIdentifierTest(jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, getName) {
            std::string expectedName = "name";
            REQUIRE_CALL(attributeMock, getName()).RETURN(expectedName);
            getNameTest(expectedName, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isReadOnly) {
            bool readOnlyValue = true;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeBooleanTest, isWritable) {
            bool readOnlyValue = false;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
