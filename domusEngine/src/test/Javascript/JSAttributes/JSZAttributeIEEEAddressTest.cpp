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
            jsZAttribute = std::make_shared<JSZAttributeIEEEAddress>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLIEEEAddressAttribute::name());
        }

        void JSZAttributeIEEEAddressTest::TearDown() {
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeIEEEAddressTest, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeIEEEAddressTest, createIstance) {
            createIstanceTest("Z" + ZCLIEEEAddressAttribute::name(), jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getValue) {
            uint64_t expectedValue = 0xFFEEDDCCBBAA9988L;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &zclIEEEAddressAttributeMock);
            EXPECT_CALL(zclIEEEAddressAttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            String::Utf8Value address(result);
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsString(), true);

            ASSERT_THAT(*address, StrCaseEq("FF-EE-DD-CC-BB-AA-99-88"));
        }

        TEST_F(JSZAttributeIEEEAddressTest, setValue) {
            std::string value = "'ff-ee-dd-cc-bb-aa-99-88'";
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << value;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &zclIEEEAddressAttributeMock);

            runScript(stream.str());
        }


        TEST_F(JSZAttributeIEEEAddressTest, requestValue) {
            EXPECT_CALL(zclIEEEAddressAttributeMock, requestValue());
            requestValueTest(jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(zclIEEEAddressAttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(zclIEEEAddressAttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(zclIEEEAddressAttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(zclIEEEAddressAttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(zclIEEEAddressAttributeMock, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getIdentifier) {
            EXPECT_CALL(zclIEEEAddressAttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(zclIEEEAddressAttributeMock, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclIEEEAddressAttributeMock);
        }

        TEST_F(JSZAttributeIEEEAddressTest, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(zclIEEEAddressAttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclIEEEAddressAttributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
