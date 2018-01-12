/*
 * JSZAttributeIEEEAddressTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeIEEEAddressTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        void JSZAttributeIEEEAddressTest::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_unique<JSZAttributeIEEEAddress>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLIEEEAddressAttribute::name());
            zclTypeExpectation = NAMED_ALLOW_CALL(attributeMock,getZCLType()).RETURN(ZCLTypeDataType::ZCLTypeIEEEaddress);
        }

        void JSZAttributeIEEEAddressTest::TearDown() {
            zclTypeExpectation.reset();
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeIEEEAddressTest, createTemplate) {
            createTemplateTest(jsZAttribute.get());
        }

        TEST_F(JSZAttributeIEEEAddressTest, createIstance) {
            createIstanceTest("Z" + ZCLIEEEAddressAttribute::name(), jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getValue) {
            uint64_t expectedValue = 0xFFEEDDCCBBAA9988L;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);
            REQUIRE_CALL(attributeMock, getValue()).RETURN(std::any(expectedValue));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            String::Utf8Value address(result);
            ASSERT_EQ(result.IsEmpty(), false);
            ASSERT_EQ(result->IsString(), true);

            //ASSERT_EQ(*address, StrCaseEq("FF-EE-DD-CC-BB-AA-99-88"));
        }

        TEST_F(JSZAttributeIEEEAddressTest, setValue) {
            std::string value = "'ff-ee-dd-cc-bb-aa-99-88'";
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << value;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);

            runScript(stream.str());
        }


        TEST_F(JSZAttributeIEEEAddressTest, isAvailable) {
            bool availableStatus = true;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isNotAvailable) {
            bool availableStatus = false;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isUnsupported) {
            bool unsupported = true;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isSupported) {
            bool unsupported = false;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getIdentifier) {
            REQUIRE_CALL(attributeMock, getIdentifier()).RETURN(ATTRIBUTE0_ID);
            getIdentifierTest(jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getName) {
            std::string expectedName = "name";
            REQUIRE_CALL(attributeMock, getName()).RETURN(expectedName);
            getNameTest(expectedName, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isReadOnly) {
            bool readOnlyValue = true;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isWritable) {
            bool readOnlyValue = false;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
